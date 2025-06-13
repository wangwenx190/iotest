#include <QCoreApplication>
#include <QDir>
#include <QLocale>
#include <QRandomGenerator>
#include <QList>
#include <QFile>
#include <QDebug>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QtConcurrentMap>
#include <QTextStream>
#include <array>
#include <clocale>
#include <memory>
#include <fstream>
#include <chrono>
#include <qt_windows.h>

#define USE_QT_TIMER 0

using namespace Qt::StringLiterals;

static constexpr const qsizetype kMaxVertexOutputCount{ 10 };
static constexpr const qsizetype kMaxElementOutputCount{ 10 };
static constexpr const qsizetype kInvalidSize{ std::numeric_limits<qsizetype>::max() };
static constexpr const auto kTxtFileName{ "test.txt"_L1 };
static constexpr const auto kBinFileName{ "test.bin"_L1 };

using IdType = quint64;
using SizeType = quint64;

struct Vertex final {
    IdType id{ 0 };
    std::array<qreal, 3> coordinate{};
};
using VertexList = QList<Vertex>;

static inline QDebug operator<<(QDebug d, const Vertex& vertex) {
    const QDebugStateSaver saver(d);
    d.noquote();
    d.nospace();
    d << "Vertex(id: " << vertex.id << ", coordinate: " << vertex.coordinate << ')';
    return d;
}

static inline QDebug operator<<(QDebug d, const VertexList& vertexList) {
    const QDebugStateSaver saver(d);
    d.noquote();
    d.nospace();
    d << "VertexList[\n";
    if (vertexList.size() > kMaxVertexOutputCount) {
        for (qsizetype i = 0; i < kMaxVertexOutputCount; ++i) {
            d << '\t' << vertexList[i];
            if (i < kMaxVertexOutputCount - 1) {
                d << ',';
            }
            d << '\n';
        }
        d << "\t... (the rest " << vertexList.size() - kMaxVertexOutputCount << " items are omitted)\n";
    } else {
        for (qsizetype i = 0; i < vertexList.size(); ++i) {
            d << '\t' << vertexList[i];
            if (i < vertexList.size() - 1) {
                d << ',';
            }
            d << '\n';
        }
    }
    d << ']';
    return d;
}

struct Hex final {
    IdType id{ 0 };
    std::array<IdType, 8> connection{};
};
using HexList = QList<Hex>;

static inline QDebug operator<<(QDebug d, const Hex& hex) {
    const QDebugStateSaver saver(d);
    d.noquote();
    d.nospace();
    d << "Hex(id: " << hex.id << ", connection: " << hex.connection << ')';
    return d;
}

static inline QDebug operator<<(QDebug d, const HexList& hexList) {
    const QDebugStateSaver saver(d);
    d.noquote();
    d.nospace();
    d << "HexList[\n";
    if (hexList.size() > kMaxElementOutputCount) {
        for (qsizetype i = 0; i < kMaxElementOutputCount; ++i) {
            d << '\t' << hexList[i];
            if (i < kMaxElementOutputCount - 1) {
                d << ',';
            }
            d << '\n';
        }
        d << "\t... (the rest " << hexList.size() - kMaxElementOutputCount << " items are omitted)\n";
    } else {
        for (qsizetype i = 0; i < hexList.size(); ++i) {
            d << '\t' << hexList[i];
            if (i < hexList.size() - 1) {
                d << ',';
            }
            d << '\n';
        }
    }
    d << ']';
    return d;
}

struct Model final {
    VertexList vertexList{};
    HexList elementList{};
};

static inline QDebug operator<<(QDebug d, const Model& model) {
    const QDebugStateSaver saver(d);
    d.noquote();
    d.nospace();
    d << "Model(vertices: " << model.vertexList << ", elements: " << model.elementList << ')';
    return d;
}

struct HandleCloser final {
    inline void operator()(HANDLE handle) const {
        if (handle && handle != INVALID_HANDLE_VALUE) {
            ::CloseHandle(handle);
        }
    }
};
using ScopedHandle = std::unique_ptr<void, HandleCloser>;

struct MemoryUnmapper final {
    inline void operator()(LPCVOID addr) const {
        if (addr) {
            ::UnmapViewOfFile(addr);
        }
    }
};
using ScopedMemory = std::unique_ptr<void, MemoryUnmapper>;

static constexpr const SizeType kFieldSize{ 8 };

static inline void generateNewTestModel(const IdType elementCount, Model& modelOut) {
    Q_ASSERT(elementCount > 0);
    Q_ASSERT(elementCount < kInvalidSize);
    modelOut.elementList.resize(elementCount);
    QtConcurrent::blockingMap(modelOut.elementList, [elementCount](Hex& hex){
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            hex.connection[vertexIndex] = QRandomGenerator::global()->bounded(IdType(0), elementCount);
        }
    });
    modelOut.vertexList.resize(elementCount * 8);
    QtConcurrent::blockingMap(modelOut.vertexList, [](Vertex& vertex){
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            vertex.coordinate[coordIndex] = QRandomGenerator::global()->bounded(qreal(10));
        }
    });
}

static inline void saveModelToBinary(const Model& model, QIODevice& io) {
    Q_ASSERT(!model.elementList.isEmpty());
    Q_ASSERT(!model.vertexList.isEmpty());
    Q_ASSERT(io.isOpen());
    Q_ASSERT(io.openMode() & QIODevice::WriteOnly);
    {
        const auto vertexCount = model.vertexList.size();
        io.write(reinterpret_cast<const char*>(&vertexCount), kFieldSize);
    }
    {
        const auto elementCount = model.elementList.size();
        io.write(reinterpret_cast<const char*>(&elementCount), kFieldSize);
    }
    for (auto&& vertex : std::as_const(model.vertexList)) {
        for (auto&& coord : std::as_const(vertex.coordinate)) {
            io.write(reinterpret_cast<const char*>(&coord), kFieldSize);
        }
    }
    for (auto&& hex : std::as_const(model.elementList)) {
        for (auto&& vertexIndex : std::as_const(hex.connection)) {
            io.write(reinterpret_cast<const char*>(&vertexIndex), kFieldSize);
        }
    }
}

static inline void saveModelToText(const Model& model, QIODevice& io) {
    Q_ASSERT(!model.elementList.isEmpty());
    Q_ASSERT(!model.vertexList.isEmpty());
    Q_ASSERT(io.isOpen());
    Q_ASSERT(io.openMode() & QIODevice::WriteOnly);
    {
        const auto vertexCount = model.vertexList.size();
        io.write(QByteArray::number(vertexCount) + '\n');
    }
    {
        const auto elementCount = model.elementList.size();
        io.write(QByteArray::number(elementCount) + '\n');
    }
    for (auto&& vertex : std::as_const(model.vertexList)) {
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            // https://cppreference.com/w/cpp/types/numeric_limits/max_digits10
            io.write(QByteArray::number(vertex.coordinate[coordIndex], 'g', std::numeric_limits<qreal>::max_digits10) + (coordIndex == vertex.coordinate.size() - 1 ? '\n' : '\t'));
        }
    }
    for (auto&& hex : std::as_const(model.elementList)) {
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            io.write(QByteArray::number(hex.connection[vertexIndex]) + (vertexIndex == hex.connection.size() - 1 ? '\n' : '\t'));
        }
    }
}

[[nodiscard]] static inline bool loadModelFromBinaryMMap(const char* data, Model& modelOut) {
    Q_ASSERT(data);
    IdType vertexCount{ 0 };
    {
        std::memcpy(&vertexCount, data, kFieldSize);
        if (vertexCount == 0 || vertexCount >= kInvalidSize) {
            qWarning() << "Vertex count is invalid.";
            return false;
        }
        qDebug() << "Vertex count:" << vertexCount;
        modelOut.vertexList.resize(vertexCount);
        for (IdType vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
            modelOut.vertexList[vertexIndex].id = vertexIndex;
        }
    }
    IdType elementCount{ 0 };
    {
        std::memcpy(&elementCount, data + kFieldSize, kFieldSize);
        if (elementCount == 0 || elementCount >= kInvalidSize) {
            qWarning() << "Element count is invalid.";
            return false;
        }
        qDebug() << "Element count:" << elementCount;
        modelOut.elementList.resize(elementCount);
        for (IdType elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
            modelOut.elementList[elementIndex].id = elementIndex;
        }
    }
    QtConcurrent::blockingMap(modelOut.vertexList, [data](Vertex& vertex){
        const SizeType offset = kFieldSize * (vertex.id * vertex.coordinate.size() + 2);
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            std::memcpy(&(vertex.coordinate[coordIndex]), data + offset + kFieldSize * coordIndex, kFieldSize);
        }
    });
    const SizeType vertexDataCount = vertexCount * 3;
    QtConcurrent::blockingMap(modelOut.elementList, [data, vertexDataCount](Hex& hex){
        const SizeType offset = kFieldSize * (hex.id * hex.connection.size() + vertexDataCount + 2);
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            std::memcpy(&(hex.connection[vertexIndex]), data + offset + kFieldSize * vertexIndex, kFieldSize);
        }
    });
    return true;
}

[[nodiscard]] static inline bool loadModelFromTextMMap(const char* data, const SizeType dataSize, Model& modelOut) {
    Q_ASSERT(data);
    Q_ASSERT(dataSize > 0);
    const auto& getNextNewLinePos = [data, dataSize](const SizeType beginOffset){
        Q_ASSERT(beginOffset < dataSize);
        quint64 pos = beginOffset;
        while (pos < dataSize) {
            if (data[pos] == '\n') {
                return pos;
            }
            ++pos;
        }
        Q_ASSERT(false);
        return SizeType(0);
    };
    const SizeType vertexCountEndPos = getNextNewLinePos(0);
    if (vertexCountEndPos == 0 || vertexCountEndPos >= dataSize) {
        qWarning() << "Failed to locate the first line.";
        return false;
    }
    IdType vertexCount{ 0 };
    {
        vertexCount = QByteArrayView(data, static_cast<qsizetype>(vertexCountEndPos)).toULongLong();
        if (vertexCount == 0 || vertexCount >= kInvalidSize) {
            qWarning() << "Vertex count is invalid.";
            return false;
        }
        qDebug() << "Vertex count:" << vertexCount;
        modelOut.vertexList.resize(vertexCount);
        for (IdType vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
            modelOut.vertexList[vertexIndex].id = vertexIndex;
        }
    }
    const SizeType elementCountEndPos = getNextNewLinePos(vertexCountEndPos + 1);
    if (elementCountEndPos - 1 <= vertexCountEndPos || elementCountEndPos >= dataSize) {
        return false;
    }
    const SizeType elementCountCharCount = elementCountEndPos - vertexCountEndPos - 1;
    Q_ASSERT(elementCountCharCount > 0);
    IdType elementCount{ 0 };
    {
        elementCount = QByteArrayView(data + vertexCountEndPos + 1, static_cast<qsizetype>(elementCountCharCount)).toULongLong();
        if (elementCount == 0 || elementCount >= kInvalidSize) {
            qWarning() << "Element count is invalid.";
            return false;
        }
        qDebug() << "Element count:" << elementCount;
        modelOut.elementList.resize(elementCount);
        for (IdType elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
            modelOut.elementList[elementIndex].id = elementIndex;
        }
    }
    struct OffsetItem final {
        IdType offset{ 0 };
        IdType size{ 0 };
    };
    QList<OffsetItem> offsetList{};
    offsetList.reserve(vertexCount + elementCount + 10);
    offsetList.emplace_back(std::move(OffsetItem(0, vertexCountEndPos)));
    offsetList.emplace_back(std::move(OffsetItem(vertexCountEndPos + 1, elementCountCharCount)));
    offsetList.emplace_back(std::move(OffsetItem(elementCountEndPos + 1, 0)));
    {
        qsizetype curOffsetIndex = 2;
        IdType curOffset = offsetList[curOffsetIndex].offset;
        while (curOffset < dataSize) {
            const IdType nextEndPos = getNextNewLinePos(curOffset);
            if (nextEndPos <= curOffset || nextEndPos >= dataSize) {
                break;
            }
            const IdType nextOffset = nextEndPos + 1;
            offsetList[curOffsetIndex].size = nextOffset - curOffset - 1;
            offsetList.emplace_back(std::move(OffsetItem(nextOffset, 0)));
            curOffset = nextOffset;
            ++curOffsetIndex;
        }
    }
    QtConcurrent::blockingMap(modelOut.vertexList, [data, &offsetList](Vertex& vertex){
        const OffsetItem& offsetData = offsetList[vertex.id + 2];
        IdType coordIndex = 0;
        for (const auto& it : QLatin1StringView(data + offsetData.offset, offsetData.size).tokenize(u'\t')) {
            vertex.coordinate[coordIndex] = it.toDouble();
            ++coordIndex;
        }
    });
    QtConcurrent::blockingMap(modelOut.elementList, [data, &offsetList, vertexCount](Hex& hex){
        const OffsetItem& offsetData = offsetList[hex.id + vertexCount + 2];
        IdType vertexIndex = 0;
        for (const auto& it : QLatin1StringView(data + offsetData.offset, offsetData.size).tokenize(u'\t')) {
            hex.connection[vertexIndex] = it.toULongLong();
            ++vertexIndex;
        }
    });
    return true;
}

[[nodiscard]] static inline bool loadModelFromBinaryFS(std::ifstream& ifs, Model& modelOut) {
    Q_ASSERT(ifs.is_open());
    IdType vertexCount = 0;
    {
        ifs.read(reinterpret_cast<char*>(&vertexCount), kFieldSize);
        if (vertexCount == 0 || vertexCount >= kInvalidSize) {
            qWarning() << "Vertex count is invalid.";
            return false;
        }
        qDebug() << "Vertex count:" << vertexCount;
        modelOut.vertexList.resize(vertexCount);
    }
    IdType elementCount = 0;
    {
        ifs.read(reinterpret_cast<char*>(&elementCount), kFieldSize);
        if (elementCount == 0 || elementCount >= kInvalidSize) {
            qWarning() << "Element count is invalid.";
            return false;
        }
        qDebug() << "Element count:" << elementCount;
        modelOut.elementList.resize(elementCount);
    }
    for (IdType vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
        Vertex& vertex = modelOut.vertexList[vertexIndex];
        vertex.id = vertexIndex;
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            ifs.read(reinterpret_cast<char*>(&(vertex.coordinate[coordIndex])), kFieldSize);
        }
    }
    for (IdType elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
        Hex& hex = modelOut.elementList[elementIndex];
        hex.id = elementIndex;
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            ifs.read(reinterpret_cast<char*>(&(hex.connection[vertexIndex])), kFieldSize);
        }
    }
    return true;
}

template <typename T>
[[nodiscard]] static inline bool loadModelFromTextStream(T& stream, Model& modelOut) {
    IdType vertexCount = 0;
    {
        stream >> vertexCount;
        if (vertexCount == 0 || vertexCount >= kInvalidSize) {
            qWarning() << "Vertex count is invalid.";
            return false;
        }
        qDebug() << "Vertex count:" << vertexCount;
        modelOut.vertexList.resize(vertexCount);
    }
    IdType elementCount = 0;
    {
        stream >> elementCount;
        if (elementCount == 0 || elementCount >= kInvalidSize) {
            qWarning() << "Element count is invalid.";
            return false;
        }
        qDebug() << "Element count:" << elementCount;
        modelOut.elementList.resize(elementCount);
    }
    for (IdType vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
        Vertex& vertex = modelOut.vertexList[vertexIndex];
        vertex.id = vertexIndex;
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            stream >> vertex.coordinate[coordIndex];
        }
    }
    for (IdType elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
        Hex& hex = modelOut.elementList[elementIndex];
        hex.id = elementIndex;
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            stream >> hex.connection[vertexIndex];
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    std::setlocale(LC_ALL, "C.UTF-8");
    QLocale::setDefault(QLocale::c());
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QCommandLineParser parser{};
    const QCommandLineOption generateOption("generate"_L1);
    parser.addOption(generateOption);
    const QCommandLineOption elementCountOption("element-count"_L1, "element count"_L1, "number"_L1);
    parser.addOption(elementCountOption);
    parser.process(application);

    if (parser.isSet(generateOption)) {
        const qint64 elementCount = parser.value(elementCountOption).toLongLong();
        if (elementCount <= 0 || elementCount >= kInvalidSize) {
            qWarning() << "You should give a valid element count number.";
            return -1;
        }
        qDebug() << "Start generating test file ...";
        Model model{};
        generateNewTestModel(elementCount, model);
        {
            qDebug() << "Generating binary data file ...";
            QFile file(kBinFileName);
            if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
                qWarning() << "Failed to open file to write:" << file.errorString();
                return -1;
            }
            saveModelToBinary(model, file);
            file.flush();
            file.close();
        }
        {
            qDebug() << "Generating text data file ...";
            QFile file(kTxtFileName);
            // Don't add "QFile::Text" here! It will make QFile translate "\n" to "\r\n" on Windows!
            // This behavior would break our text parsing algorithm!
            if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
                qWarning() << "Failed to open file to write:" << file.errorString();
                return -1;
            }
            saveModelToText(model, file);
            file.flush();
            file.close();
        }
        qDebug() << "Finished test file generation.";
        return 0;
    }

    qDebug() << "Loading file ...";

    {
        qDebug() << "[binary, mmap] start loading ...";
#if USE_QT_TIMER
        QElapsedTimer timer{};
        timer.start();
#else
        const auto beginTime = std::chrono::high_resolution_clock::now();
#endif
        const auto hFile = ScopedHandle{ ::CreateFileA(kBinFileName.constData(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr) };
        if (!hFile || hFile.get() == INVALID_HANDLE_VALUE) {
            qWarning() << "CreateFile() failed.";
            return -1;
        }
        SizeType dataSize = 0;
        {
            LARGE_INTEGER li{};
            std::memset(&li, 0, sizeof(li));
            if (!::GetFileSizeEx(hFile.get(), &li)) {
                qWarning() << "Failed to retrieve file size.";
                return -1;
            }
            dataSize = li.QuadPart;
        }
        if (dataSize == 0 || dataSize >= kInvalidSize) {
            qWarning() << "File size is invalid.";
            return -1;
        }
        qDebug().noquote() << "File size:" << dataSize << "bytes (" << QLocale().formattedDataSize(dataSize) << ')';
        const auto hMapFile = ScopedHandle{ ::CreateFileMappingA(hFile.get(), nullptr, PAGE_READONLY, 0, 0, nullptr) };
        if (!hMapFile || hMapFile.get() == INVALID_HANDLE_VALUE) {
            qWarning() << "CreateFileMapping() failed.";
            return -1;
        }
        const auto pBuffer = ScopedMemory{ ::MapViewOfFile(hMapFile.get(), FILE_MAP_READ, 0, 0, 0) };
        if (!pBuffer) {
            qWarning() << "MapViewOfFile() failed.";
            return -1;
        }
        const auto data = static_cast<const char*>(pBuffer.get());
        Model model{};
        if (!loadModelFromBinaryMMap(data, model)) {
            qWarning() << "Failed to load model from binary data.";
            return -1;
        }
        qDebug() << "Finished loading.";
#if USE_QT_TIMER
        qDebug() << "Total elapsed time:" << timer.elapsed() << "ms.";
#else
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - beginTime);
        qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
        qDebug() << model;
    }

    {
        qDebug() << "[text, mmap] start loading ...";
#if USE_QT_TIMER
        QElapsedTimer timer{};
        timer.start();
#else
        const auto beginTime = std::chrono::high_resolution_clock::now();
#endif
        const auto hFile = ScopedHandle{ ::CreateFileA(kTxtFileName.constData(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr) };
        if (!hFile || hFile.get() == INVALID_HANDLE_VALUE) {
            qWarning() << "CreateFile() failed.";
            return -1;
        }
        SizeType dataSize = 0;
        {
            LARGE_INTEGER li{};
            std::memset(&li, 0, sizeof(li));
            if (!::GetFileSizeEx(hFile.get(), &li)) {
                qWarning() << "Failed to retrieve file size.";
                return -1;
            }
            dataSize = li.QuadPart;
        }
        if (dataSize == 0 || dataSize >= kInvalidSize) {
            qWarning() << "File size is invalid.";
            return -1;
        }
        qDebug().noquote() << "File size:" << dataSize << "bytes (" << QLocale().formattedDataSize(dataSize) << ')';
        const auto hMapFile = ScopedHandle{ ::CreateFileMappingA(hFile.get(), nullptr, PAGE_READONLY, 0, 0, nullptr) };
        if (!hMapFile || hMapFile.get() == INVALID_HANDLE_VALUE) {
            qWarning() << "CreateFileMapping() failed.";
            return -1;
        }
        const auto pBuffer = ScopedMemory{ ::MapViewOfFile(hMapFile.get(), FILE_MAP_READ, 0, 0, 0) };
        if (!pBuffer) {
            qWarning() << "MapViewOfFile() failed.";
            return -1;
        }
        const auto data = static_cast<const char*>(pBuffer.get());
        Model model{};
        if (!loadModelFromTextMMap(data, dataSize, model)) {
            qWarning() << "Failed to load model from text data.";
            return -1;
        }
        qDebug() << "Finished loading.";
#if USE_QT_TIMER
        qDebug() << "Total elapsed time:" << timer.elapsed() << "ms.";
#else
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - beginTime);
        qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
        qDebug() << model;
    }

    {
        qDebug() << "[binary, fstream] start loading ...";
#if USE_QT_TIMER
        QElapsedTimer timer{};
        timer.start();
#else
        const auto beginTime = std::chrono::high_resolution_clock::now();
#endif
        std::ifstream ifs(kBinFileName.constData(), std::ios::in | std::ios::binary);
        if (!ifs.is_open()) {
            qWarning() << "Failed to open file to read.";
            return -1;
        }
        Model model{};
        if (!loadModelFromBinaryFS(ifs, model)) {
            qWarning() << "Failed to load model from binary data.";
            return -1;
        }
        qDebug() << "Finished loading.";
#if USE_QT_TIMER
        qDebug() << "Total elapsed time:" << timer.elapsed() << "ms.";
#else
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - beginTime);
        qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
        qDebug() << model;
    }

    {
        qDebug() << "[text, fstream] start loading ...";
#if USE_QT_TIMER
        QElapsedTimer timer{};
        timer.start();
#else
        const auto beginTime = std::chrono::high_resolution_clock::now();
#endif
        std::ifstream ifs(kTxtFileName.constData());
        if (!ifs.is_open()) {
            qWarning() << "Failed to open file to read.";
            return -1;
        }
        Model model{};
        if (!loadModelFromTextStream(ifs, model)) {
            qWarning() << "Failed to load model from text data.";
            return -1;
        }
        qDebug() << "Finished loading.";
#if USE_QT_TIMER
        qDebug() << "Total elapsed time:" << timer.elapsed() << "ms.";
#else
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - beginTime);
        qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
        qDebug() << model;
    }

    {
        qDebug() << "[text, QTextStream] start loading ...";
#if USE_QT_TIMER
        QElapsedTimer timer{};
        timer.start();
#else
        const auto beginTime = std::chrono::high_resolution_clock::now();
#endif
        QFile file(kTxtFileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qWarning() << "Failed to open file to read.";
            return -1;
        }
        QTextStream qts(&file);
        Model model{};
        if (!loadModelFromTextStream(qts, model)) {
            qWarning() << "Failed to load model from text data.";
            return -1;
        }
        file.close();
        qDebug() << "Finished loading.";
#if USE_QT_TIMER
        qDebug() << "Total elapsed time:" << timer.elapsed() << "ms.";
#else
        const auto endTime = std::chrono::high_resolution_clock::now();
        const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - beginTime);
        qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
        qDebug() << model;
    }

    return 0;
}
