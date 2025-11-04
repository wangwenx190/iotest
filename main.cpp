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
#include <fstream>
#include <chrono>

#define USE_QT_TIMER 0

using namespace Qt::StringLiterals;

using IdType = quint64;
using SizeType = quint64;

static constexpr const qsizetype kMaxVertexOutputCount{ 10 };
static constexpr const qsizetype kMaxElementOutputCount{ 10 };
static constexpr const qsizetype kInvalidSize{ std::numeric_limits<qsizetype>::max() };
static constexpr const auto kTxtFileName{ "test.txt"_L1 };
static constexpr const auto kBinFileName{ "test.bin"_L1 };
static constexpr const SizeType kFieldSize{ 8 };

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

static bool g_multiThreadEnabled{ false };

static inline void generateNewTestModel(const IdType elementCount, Model& modelOut) {
    Q_ASSERT(elementCount > 0);
    Q_ASSERT(elementCount < kInvalidSize);
    modelOut.elementList.resize(elementCount);
    for (IdType elementIndex = 0; elementIndex < elementCount; ++elementIndex) {
        modelOut.elementList[elementIndex].id = elementIndex;
    }
    const auto& fillNewHex = [elementCount](Hex& hex){
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            hex.connection[vertexIndex] = QRandomGenerator::global()->bounded(IdType(0), elementCount);
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.elementList, [&fillNewHex](Hex& hex){
            fillNewHex(hex);
        });
    } else {
        for (Hex& hex : modelOut.elementList) {
            fillNewHex(hex);
        }
    }
    const SizeType vertexCount = elementCount * 8;
    modelOut.vertexList.resize(vertexCount);
    for (IdType vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex) {
        modelOut.vertexList[vertexIndex].id = vertexIndex;
    }
    const auto& fillNewVertex = [](Vertex& vertex){
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            vertex.coordinate[coordIndex] = QRandomGenerator::global()->bounded(qreal(10));
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.vertexList, [&fillNewVertex](Vertex& vertex){
            fillNewVertex(vertex);
        });
    } else {
        for (Vertex& vertex : modelOut.vertexList) {
            fillNewVertex(vertex);
        }
    }
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

[[nodiscard]] static inline bool loadModelFromBinaryMMap(const std::byte* data, Model& modelOut) {
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
    const auto& fillVertex = [data](Vertex& vertex){
        const SizeType offset = kFieldSize * (vertex.id * vertex.coordinate.size() + 2);
        for (IdType coordIndex = 0; coordIndex < vertex.coordinate.size(); ++coordIndex) {
            std::memcpy(&(vertex.coordinate[coordIndex]), data + offset + kFieldSize * coordIndex, kFieldSize);
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.vertexList, [&fillVertex](Vertex& vertex){
            fillVertex(vertex);
        });
    } else {
        for (Vertex& vertex : modelOut.vertexList) {
            fillVertex(vertex);
        }
    }
    const SizeType vertexDataCount = vertexCount * 3;
    const auto& fillHex = [data, vertexDataCount](Hex& hex){
        const SizeType offset = kFieldSize * (hex.id * hex.connection.size() + vertexDataCount + 2);
        for (IdType vertexIndex = 0; vertexIndex < hex.connection.size(); ++vertexIndex) {
            std::memcpy(&(hex.connection[vertexIndex]), data + offset + kFieldSize * vertexIndex, kFieldSize);
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.elementList, [&fillHex](Hex& hex){
            fillHex(hex);
        });
    } else {
        for (Hex& hex : modelOut.elementList) {
            fillHex(hex);
        }
    }
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
    const auto& fillVertex = [data, &offsetList](Vertex& vertex){
        const OffsetItem& offsetData = offsetList[vertex.id + 2];
        IdType coordIndex = 0;
        for (const auto& it : QLatin1StringView(data + offsetData.offset, offsetData.size).tokenize(u'\t')) {
            vertex.coordinate[coordIndex] = it.toDouble();
            ++coordIndex;
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.vertexList, [&fillVertex](Vertex& vertex){
            fillVertex(vertex);
        });
    } else {
        for (Vertex& vertex : modelOut.vertexList) {
            fillVertex(vertex);
        }
    }
    const auto& fillHex = [data, &offsetList, vertexCount](Hex& hex){
        const OffsetItem& offsetData = offsetList[hex.id + vertexCount + 2];
        IdType vertexIndex = 0;
        for (const auto& it : QLatin1StringView(data + offsetData.offset, offsetData.size).tokenize(u'\t')) {
            hex.connection[vertexIndex] = it.toULongLong();
            ++vertexIndex;
        }
    };
    if (g_multiThreadEnabled) {
        QtConcurrent::blockingMap(modelOut.elementList, [&fillHex](Hex& hex){
            fillHex(hex);
        });
    } else {
        for (Hex& hex : modelOut.elementList) {
            fillHex(hex);
        }
    }
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

struct TimeRecorder final {
    TimeRecorder();
    ~TimeRecorder();

    void dismiss();
    void report();

private:
    bool m_dismissed = false;
#if USE_QT_TIMER
    QElapsedTimer m_timer;
#else
    std::chrono::high_resolution_clock::time_point m_beginTime;
#endif
};

TimeRecorder::TimeRecorder() {
#if USE_QT_TIMER
    m_timer.start();
#else
    m_beginTime = std::chrono::high_resolution_clock::now();
#endif
}

TimeRecorder::~TimeRecorder() {
    report();
}

void TimeRecorder::dismiss() {
    m_dismissed = true;
}

void TimeRecorder::report() {
    if (m_dismissed) {
        return;
    }
    m_dismissed = true;
#if USE_QT_TIMER
    qDebug() << "Total elapsed time:" << m_timer.elapsed() << "ms.";
#else
    const auto endTime = std::chrono::high_resolution_clock::now();
    const auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - m_beginTime);
    qDebug() << "Total elapsed time:" << elapsedTime.count() << "ms.";
#endif
}

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("IO Tester"_L1);
    QCoreApplication::setApplicationVersion("1.0.0.0"_L1);

    QCoreApplication application(argc, argv);

    std::setlocale(LC_ALL, "C.UTF-8");
    QLocale::setDefault(QLocale::c());
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QCommandLineParser parser{};
    parser.setApplicationDescription("A small program to test some specific IO performance."_L1);
    parser.addVersionOption();
    parser.addHelpOption();
    const QCommandLineOption generateOption("generate"_L1, "Generate test data file."_L1);
    parser.addOption(generateOption);
    const QCommandLineOption elementCountOption("element-count"_L1, "Set test file's element count. 1 element = 8 uint64 + 24 double."_L1, "number"_L1);
    parser.addOption(elementCountOption);
    const QCommandLineOption multiThreadOption("multi-thread"_L1, "Use multi-thread technology whenever possible (MinGW's thread implementation is very slow on Windows, be careful)."_L1);
    parser.addOption(multiThreadOption);
    const QCommandLineOption textOption("text"_L1, "Enable text data file generation/parsing test (may be very time consuming, be careful)."_L1);
    parser.addOption(textOption);
    parser.process(application);

    g_multiThreadEnabled = parser.isSet(multiThreadOption);
    const bool textEnabled = parser.isSet(textOption);

    qDebug() << (g_multiThreadEnabled ? "<MULTI-THREAD MODE>" : "<SINGLE-THREAD MODE>");

    if (parser.isSet(generateOption)) {
        const qint64 elementCount = parser.value(elementCountOption).toLongLong();
        if (elementCount <= 0 || elementCount >= kInvalidSize) {
            qWarning() << "You should give a valid element count number.";
            return -1;
        }
        Model model{};
        {
            [[maybe_unused]] TimeRecorder time{};
            qDebug() << "Generating test data ...";
            generateNewTestModel(elementCount, model);
        }
        {
            [[maybe_unused]] TimeRecorder time{};
            qDebug() << "Writing binary data file ...";
            QFile file(kBinFileName);
            if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
                qWarning() << "Failed to open file to write:" << file.errorString();
                return -1;
            }
            saveModelToBinary(model, file);
            file.flush();
            file.close();
        }
        if (textEnabled) {
            [[maybe_unused]] TimeRecorder time{};
            qDebug() << "Writing text data file ...";
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
        qDebug() << "Finished test data file generation.";
        return 0;
    }

    qDebug() << "Start testing loading and parsing performance ...";

    {
        [[maybe_unused]] TimeRecorder time{};
        qDebug() << "---------- [binary, mmap] ----------";
        QFile file(kBinFileName);
        if (!file.open(QFile::ReadOnly)) {
            qWarning() << "Failed to open file:" << file.errorString();
            return -1;
        }
        const qint64 dataSize = file.size();
        if (dataSize <= 0 || dataSize >= kInvalidSize) {
            qWarning() << "File size is invalid.";
            return -1;
        }
        qDebug().noquote().nospace() << "File size: " << dataSize << " bytes (" << QLocale().formattedDataSize(dataSize) << ')';
        const auto buffer = reinterpret_cast<const std::byte*>(file.map(0, dataSize));
        if (!buffer) {
            qWarning() << "Failed to map file to memory:" << file.errorString();
            return -1;
        }
        Model model{};
        if (!loadModelFromBinaryMMap(buffer, model)) {
            qWarning() << "Failed to load model from binary data.";
            return -1;
        }
        qDebug() << model;
        qDebug() << "Finished testing.";
    }

    if (textEnabled) {
        [[maybe_unused]] TimeRecorder time{};
        qDebug() << "---------- [text, mmap] ----------";
        QFile file(kTxtFileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            qWarning() << "Failed to open file:" << file.errorString();
            return -1;
        }
        const qint64 dataSize = file.size();
        if (dataSize <= 0 || dataSize >= kInvalidSize) {
            qWarning() << "File size is invalid.";
            return -1;
        }
        qDebug().noquote().nospace() << "File size: " << dataSize << " bytes (" << QLocale().formattedDataSize(dataSize) << ')';
        const auto buffer = reinterpret_cast<const char*>(file.map(0, dataSize));
        if (!buffer) {
            qWarning() << "Failed to map file to memory:" << file.errorString();
            return -1;
        }
        Model model{};
        if (!loadModelFromTextMMap(buffer, dataSize, model)) {
            qWarning() << "Failed to load model from text data.";
            return -1;
        }
        qDebug() << model;
        qDebug() << "Finished testing.";
    }

    {
        [[maybe_unused]] TimeRecorder time{};
        qDebug() << "---------- [binary, fstream] ----------";
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
        ifs.close();
        qDebug() << model;
        qDebug() << "Finished testing.";
    }

    if (textEnabled) {
        [[maybe_unused]] TimeRecorder time{};
        qDebug() << "---------- [text, fstream] ----------";
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
        ifs.close();
        qDebug() << model;
        qDebug() << "Finished testing.";
    }

    if (textEnabled) {
        [[maybe_unused]] TimeRecorder time{};
        qDebug() << "---------- [text, QTextStream] ----------";
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
        qDebug() << model;
        qDebug() << "Finished testing.";
    }

    return 0;
}
