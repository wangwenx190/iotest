#pragma once

#include <cstring>

namespace IOTest::Detail {

#ifdef _DEBUG
    inline void fast_memcpy(void* dest, const void* src, const std::size_t size) { std::memcpy(dest, src, size); }
    [[nodiscard]] inline int fast_memcmp(const void* buf1, const void* buf2, const std::size_t size) { return std::memcmp(buf1, buf2, size); }
    inline void fast_memset(void* dest, const int value, const std::size_t size) { std::memset(dest, value, size); }
    [[nodiscard]] inline void* fast_memmove(void* dest, const void* src, const std::size_t count) { return std::memmove(dest, src, count); }
#else // !_DEBUG
    template <std::size_t SIZE>
    inline void memcpy_fixed(void* dest, const void* src) {
        std::memcpy(dest, src, SIZE);
    }

    template <std::size_t SIZE>
    [[nodiscard]] inline int memcmp_fixed(const void* buf1, const void* buf2) {
        return std::memcmp(buf1, buf2, SIZE);
    }

    template <std::size_t SIZE>
    inline void memset_fixed(void* dest, const int value) {
        std::memset(dest, value, SIZE);
    }

    template <std::size_t COUNT>
    [[nodiscard]] inline void* memmove_fixed(void* dest, const void* src) {
        return std::memmove(dest, src, COUNT);
    }

    inline void fast_memcpy(void* dest, const void* src, const std::size_t size) {
        switch (size) {
        case 0:
            return;
        case 1:
            return memcpy_fixed<1>(dest, src);
        case 2:
            return memcpy_fixed<2>(dest, src);
        case 3:
            return memcpy_fixed<3>(dest, src);
        case 4:
            return memcpy_fixed<4>(dest, src);
        case 5:
            return memcpy_fixed<5>(dest, src);
        case 6:
            return memcpy_fixed<6>(dest, src);
        case 7:
            return memcpy_fixed<7>(dest, src);
        case 8:
            return memcpy_fixed<8>(dest, src);
        case 9:
            return memcpy_fixed<9>(dest, src);
        case 10:
            return memcpy_fixed<10>(dest, src);
        case 11:
            return memcpy_fixed<11>(dest, src);
        case 12:
            return memcpy_fixed<12>(dest, src);
        case 13:
            return memcpy_fixed<13>(dest, src);
        case 14:
            return memcpy_fixed<14>(dest, src);
        case 15:
            return memcpy_fixed<15>(dest, src);
        case 16:
            return memcpy_fixed<16>(dest, src);
        case 17:
            return memcpy_fixed<17>(dest, src);
        case 18:
            return memcpy_fixed<18>(dest, src);
        case 19:
            return memcpy_fixed<19>(dest, src);
        case 20:
            return memcpy_fixed<20>(dest, src);
        case 21:
            return memcpy_fixed<21>(dest, src);
        case 22:
            return memcpy_fixed<22>(dest, src);
        case 23:
            return memcpy_fixed<23>(dest, src);
        case 24:
            return memcpy_fixed<24>(dest, src);
        case 25:
            return memcpy_fixed<25>(dest, src);
        case 26:
            return memcpy_fixed<26>(dest, src);
        case 27:
            return memcpy_fixed<27>(dest, src);
        case 28:
            return memcpy_fixed<28>(dest, src);
        case 29:
            return memcpy_fixed<29>(dest, src);
        case 30:
            return memcpy_fixed<30>(dest, src);
        case 31:
            return memcpy_fixed<31>(dest, src);
        case 32:
            return memcpy_fixed<32>(dest, src);
        case 33:
            return memcpy_fixed<33>(dest, src);
        case 34:
            return memcpy_fixed<34>(dest, src);
        case 35:
            return memcpy_fixed<35>(dest, src);
        case 36:
            return memcpy_fixed<36>(dest, src);
        case 37:
            return memcpy_fixed<37>(dest, src);
        case 38:
            return memcpy_fixed<38>(dest, src);
        case 39:
            return memcpy_fixed<39>(dest, src);
        case 40:
            return memcpy_fixed<40>(dest, src);
        case 41:
            return memcpy_fixed<41>(dest, src);
        case 42:
            return memcpy_fixed<42>(dest, src);
        case 43:
            return memcpy_fixed<43>(dest, src);
        case 44:
            return memcpy_fixed<44>(dest, src);
        case 45:
            return memcpy_fixed<45>(dest, src);
        case 46:
            return memcpy_fixed<46>(dest, src);
        case 47:
            return memcpy_fixed<47>(dest, src);
        case 48:
            return memcpy_fixed<48>(dest, src);
        case 49:
            return memcpy_fixed<49>(dest, src);
        case 50:
            return memcpy_fixed<50>(dest, src);
        case 51:
            return memcpy_fixed<51>(dest, src);
        case 52:
            return memcpy_fixed<52>(dest, src);
        case 53:
            return memcpy_fixed<53>(dest, src);
        case 54:
            return memcpy_fixed<54>(dest, src);
        case 55:
            return memcpy_fixed<55>(dest, src);
        case 56:
            return memcpy_fixed<56>(dest, src);
        case 57:
            return memcpy_fixed<57>(dest, src);
        case 58:
            return memcpy_fixed<58>(dest, src);
        case 59:
            return memcpy_fixed<59>(dest, src);
        case 60:
            return memcpy_fixed<60>(dest, src);
        case 61:
            return memcpy_fixed<61>(dest, src);
        case 62:
            return memcpy_fixed<62>(dest, src);
        case 63:
            return memcpy_fixed<63>(dest, src);
        case 64:
            return memcpy_fixed<64>(dest, src);
        case 65:
            return memcpy_fixed<65>(dest, src);
        case 66:
            return memcpy_fixed<66>(dest, src);
        case 67:
            return memcpy_fixed<67>(dest, src);
        case 68:
            return memcpy_fixed<68>(dest, src);
        case 69:
            return memcpy_fixed<69>(dest, src);
        case 70:
            return memcpy_fixed<70>(dest, src);
        case 71:
            return memcpy_fixed<71>(dest, src);
        case 72:
            return memcpy_fixed<72>(dest, src);
        case 73:
            return memcpy_fixed<73>(dest, src);
        case 74:
            return memcpy_fixed<74>(dest, src);
        case 75:
            return memcpy_fixed<75>(dest, src);
        case 76:
            return memcpy_fixed<76>(dest, src);
        case 77:
            return memcpy_fixed<77>(dest, src);
        case 78:
            return memcpy_fixed<78>(dest, src);
        case 79:
            return memcpy_fixed<79>(dest, src);
        case 80:
            return memcpy_fixed<80>(dest, src);
        case 81:
            return memcpy_fixed<81>(dest, src);
        case 82:
            return memcpy_fixed<82>(dest, src);
        case 83:
            return memcpy_fixed<83>(dest, src);
        case 84:
            return memcpy_fixed<84>(dest, src);
        case 85:
            return memcpy_fixed<85>(dest, src);
        case 86:
            return memcpy_fixed<86>(dest, src);
        case 87:
            return memcpy_fixed<87>(dest, src);
        case 88:
            return memcpy_fixed<88>(dest, src);
        case 89:
            return memcpy_fixed<89>(dest, src);
        case 90:
            return memcpy_fixed<90>(dest, src);
        case 91:
            return memcpy_fixed<91>(dest, src);
        case 92:
            return memcpy_fixed<92>(dest, src);
        case 93:
            return memcpy_fixed<93>(dest, src);
        case 94:
            return memcpy_fixed<94>(dest, src);
        case 95:
            return memcpy_fixed<95>(dest, src);
        case 96:
            return memcpy_fixed<96>(dest, src);
        case 97:
            return memcpy_fixed<97>(dest, src);
        case 98:
            return memcpy_fixed<98>(dest, src);
        case 99:
            return memcpy_fixed<99>(dest, src);
        case 100:
            return memcpy_fixed<100>(dest, src);
        case 101:
            return memcpy_fixed<101>(dest, src);
        case 102:
            return memcpy_fixed<102>(dest, src);
        case 103:
            return memcpy_fixed<103>(dest, src);
        case 104:
            return memcpy_fixed<104>(dest, src);
        case 105:
            return memcpy_fixed<105>(dest, src);
        case 106:
            return memcpy_fixed<106>(dest, src);
        case 107:
            return memcpy_fixed<107>(dest, src);
        case 108:
            return memcpy_fixed<108>(dest, src);
        case 109:
            return memcpy_fixed<109>(dest, src);
        case 110:
            return memcpy_fixed<110>(dest, src);
        case 111:
            return memcpy_fixed<111>(dest, src);
        case 112:
            return memcpy_fixed<112>(dest, src);
        case 113:
            return memcpy_fixed<113>(dest, src);
        case 114:
            return memcpy_fixed<114>(dest, src);
        case 115:
            return memcpy_fixed<115>(dest, src);
        case 116:
            return memcpy_fixed<116>(dest, src);
        case 117:
            return memcpy_fixed<117>(dest, src);
        case 118:
            return memcpy_fixed<118>(dest, src);
        case 119:
            return memcpy_fixed<119>(dest, src);
        case 120:
            return memcpy_fixed<120>(dest, src);
        case 121:
            return memcpy_fixed<121>(dest, src);
        case 122:
            return memcpy_fixed<122>(dest, src);
        case 123:
            return memcpy_fixed<123>(dest, src);
        case 124:
            return memcpy_fixed<124>(dest, src);
        case 125:
            return memcpy_fixed<125>(dest, src);
        case 126:
            return memcpy_fixed<126>(dest, src);
        case 127:
            return memcpy_fixed<127>(dest, src);
        case 128:
            return memcpy_fixed<128>(dest, src);
        case 129:
            return memcpy_fixed<129>(dest, src);
        case 130:
            return memcpy_fixed<130>(dest, src);
        case 131:
            return memcpy_fixed<131>(dest, src);
        case 132:
            return memcpy_fixed<132>(dest, src);
        case 133:
            return memcpy_fixed<133>(dest, src);
        case 134:
            return memcpy_fixed<134>(dest, src);
        case 135:
            return memcpy_fixed<135>(dest, src);
        case 136:
            return memcpy_fixed<136>(dest, src);
        case 137:
            return memcpy_fixed<137>(dest, src);
        case 138:
            return memcpy_fixed<138>(dest, src);
        case 139:
            return memcpy_fixed<139>(dest, src);
        case 140:
            return memcpy_fixed<140>(dest, src);
        case 141:
            return memcpy_fixed<141>(dest, src);
        case 142:
            return memcpy_fixed<142>(dest, src);
        case 143:
            return memcpy_fixed<143>(dest, src);
        case 144:
            return memcpy_fixed<144>(dest, src);
        case 145:
            return memcpy_fixed<145>(dest, src);
        case 146:
            return memcpy_fixed<146>(dest, src);
        case 147:
            return memcpy_fixed<147>(dest, src);
        case 148:
            return memcpy_fixed<148>(dest, src);
        case 149:
            return memcpy_fixed<149>(dest, src);
        case 150:
            return memcpy_fixed<150>(dest, src);
        case 151:
            return memcpy_fixed<151>(dest, src);
        case 152:
            return memcpy_fixed<152>(dest, src);
        case 153:
            return memcpy_fixed<153>(dest, src);
        case 154:
            return memcpy_fixed<154>(dest, src);
        case 155:
            return memcpy_fixed<155>(dest, src);
        case 156:
            return memcpy_fixed<156>(dest, src);
        case 157:
            return memcpy_fixed<157>(dest, src);
        case 158:
            return memcpy_fixed<158>(dest, src);
        case 159:
            return memcpy_fixed<159>(dest, src);
        case 160:
            return memcpy_fixed<160>(dest, src);
        case 161:
            return memcpy_fixed<161>(dest, src);
        case 162:
            return memcpy_fixed<162>(dest, src);
        case 163:
            return memcpy_fixed<163>(dest, src);
        case 164:
            return memcpy_fixed<164>(dest, src);
        case 165:
            return memcpy_fixed<165>(dest, src);
        case 166:
            return memcpy_fixed<166>(dest, src);
        case 167:
            return memcpy_fixed<167>(dest, src);
        case 168:
            return memcpy_fixed<168>(dest, src);
        case 169:
            return memcpy_fixed<169>(dest, src);
        case 170:
            return memcpy_fixed<170>(dest, src);
        case 171:
            return memcpy_fixed<171>(dest, src);
        case 172:
            return memcpy_fixed<172>(dest, src);
        case 173:
            return memcpy_fixed<173>(dest, src);
        case 174:
            return memcpy_fixed<174>(dest, src);
        case 175:
            return memcpy_fixed<175>(dest, src);
        case 176:
            return memcpy_fixed<176>(dest, src);
        case 177:
            return memcpy_fixed<177>(dest, src);
        case 178:
            return memcpy_fixed<178>(dest, src);
        case 179:
            return memcpy_fixed<179>(dest, src);
        case 180:
            return memcpy_fixed<180>(dest, src);
        case 181:
            return memcpy_fixed<181>(dest, src);
        case 182:
            return memcpy_fixed<182>(dest, src);
        case 183:
            return memcpy_fixed<183>(dest, src);
        case 184:
            return memcpy_fixed<184>(dest, src);
        case 185:
            return memcpy_fixed<185>(dest, src);
        case 186:
            return memcpy_fixed<186>(dest, src);
        case 187:
            return memcpy_fixed<187>(dest, src);
        case 188:
            return memcpy_fixed<188>(dest, src);
        case 189:
            return memcpy_fixed<189>(dest, src);
        case 190:
            return memcpy_fixed<190>(dest, src);
        case 191:
            return memcpy_fixed<191>(dest, src);
        case 192:
            return memcpy_fixed<192>(dest, src);
        case 193:
            return memcpy_fixed<193>(dest, src);
        case 194:
            return memcpy_fixed<194>(dest, src);
        case 195:
            return memcpy_fixed<195>(dest, src);
        case 196:
            return memcpy_fixed<196>(dest, src);
        case 197:
            return memcpy_fixed<197>(dest, src);
        case 198:
            return memcpy_fixed<198>(dest, src);
        case 199:
            return memcpy_fixed<199>(dest, src);
        case 200:
            return memcpy_fixed<200>(dest, src);
        case 201:
            return memcpy_fixed<201>(dest, src);
        case 202:
            return memcpy_fixed<202>(dest, src);
        case 203:
            return memcpy_fixed<203>(dest, src);
        case 204:
            return memcpy_fixed<204>(dest, src);
        case 205:
            return memcpy_fixed<205>(dest, src);
        case 206:
            return memcpy_fixed<206>(dest, src);
        case 207:
            return memcpy_fixed<207>(dest, src);
        case 208:
            return memcpy_fixed<208>(dest, src);
        case 209:
            return memcpy_fixed<209>(dest, src);
        case 210:
            return memcpy_fixed<210>(dest, src);
        case 211:
            return memcpy_fixed<211>(dest, src);
        case 212:
            return memcpy_fixed<212>(dest, src);
        case 213:
            return memcpy_fixed<213>(dest, src);
        case 214:
            return memcpy_fixed<214>(dest, src);
        case 215:
            return memcpy_fixed<215>(dest, src);
        case 216:
            return memcpy_fixed<216>(dest, src);
        case 217:
            return memcpy_fixed<217>(dest, src);
        case 218:
            return memcpy_fixed<218>(dest, src);
        case 219:
            return memcpy_fixed<219>(dest, src);
        case 220:
            return memcpy_fixed<220>(dest, src);
        case 221:
            return memcpy_fixed<221>(dest, src);
        case 222:
            return memcpy_fixed<222>(dest, src);
        case 223:
            return memcpy_fixed<223>(dest, src);
        case 224:
            return memcpy_fixed<224>(dest, src);
        case 225:
            return memcpy_fixed<225>(dest, src);
        case 226:
            return memcpy_fixed<226>(dest, src);
        case 227:
            return memcpy_fixed<227>(dest, src);
        case 228:
            return memcpy_fixed<228>(dest, src);
        case 229:
            return memcpy_fixed<229>(dest, src);
        case 230:
            return memcpy_fixed<230>(dest, src);
        case 231:
            return memcpy_fixed<231>(dest, src);
        case 232:
            return memcpy_fixed<232>(dest, src);
        case 233:
            return memcpy_fixed<233>(dest, src);
        case 234:
            return memcpy_fixed<234>(dest, src);
        case 235:
            return memcpy_fixed<235>(dest, src);
        case 236:
            return memcpy_fixed<236>(dest, src);
        case 237:
            return memcpy_fixed<237>(dest, src);
        case 238:
            return memcpy_fixed<238>(dest, src);
        case 239:
            return memcpy_fixed<239>(dest, src);
        case 240:
            return memcpy_fixed<240>(dest, src);
        case 241:
            return memcpy_fixed<241>(dest, src);
        case 242:
            return memcpy_fixed<242>(dest, src);
        case 243:
            return memcpy_fixed<243>(dest, src);
        case 244:
            return memcpy_fixed<244>(dest, src);
        case 245:
            return memcpy_fixed<245>(dest, src);
        case 246:
            return memcpy_fixed<246>(dest, src);
        case 247:
            return memcpy_fixed<247>(dest, src);
        case 248:
            return memcpy_fixed<248>(dest, src);
        case 249:
            return memcpy_fixed<249>(dest, src);
        case 250:
            return memcpy_fixed<250>(dest, src);
        case 251:
            return memcpy_fixed<251>(dest, src);
        case 252:
            return memcpy_fixed<252>(dest, src);
        case 253:
            return memcpy_fixed<253>(dest, src);
        case 254:
            return memcpy_fixed<254>(dest, src);
        case 255:
            return memcpy_fixed<255>(dest, src);
        case 256:
            return memcpy_fixed<256>(dest, src);
        default:
            std::memcpy(dest, src, size);
        }
    }

    [[nodiscard]] inline int fast_memcmp(const void* buf1, const void* buf2, const std::size_t size) {
        switch (size) {
        case 0:
            return 0;
        case 1:
            return memcmp_fixed<1>(buf1, buf2);
        case 2:
            return memcmp_fixed<2>(buf1, buf2);
        case 3:
            return memcmp_fixed<3>(buf1, buf2);
        case 4:
            return memcmp_fixed<4>(buf1, buf2);
        case 5:
            return memcmp_fixed<5>(buf1, buf2);
        case 6:
            return memcmp_fixed<6>(buf1, buf2);
        case 7:
            return memcmp_fixed<7>(buf1, buf2);
        case 8:
            return memcmp_fixed<8>(buf1, buf2);
        case 9:
            return memcmp_fixed<9>(buf1, buf2);
        case 10:
            return memcmp_fixed<10>(buf1, buf2);
        case 11:
            return memcmp_fixed<11>(buf1, buf2);
        case 12:
            return memcmp_fixed<12>(buf1, buf2);
        case 13:
            return memcmp_fixed<13>(buf1, buf2);
        case 14:
            return memcmp_fixed<14>(buf1, buf2);
        case 15:
            return memcmp_fixed<15>(buf1, buf2);
        case 16:
            return memcmp_fixed<16>(buf1, buf2);
        case 17:
            return memcmp_fixed<17>(buf1, buf2);
        case 18:
            return memcmp_fixed<18>(buf1, buf2);
        case 19:
            return memcmp_fixed<19>(buf1, buf2);
        case 20:
            return memcmp_fixed<20>(buf1, buf2);
        case 21:
            return memcmp_fixed<21>(buf1, buf2);
        case 22:
            return memcmp_fixed<22>(buf1, buf2);
        case 23:
            return memcmp_fixed<23>(buf1, buf2);
        case 24:
            return memcmp_fixed<24>(buf1, buf2);
        case 25:
            return memcmp_fixed<25>(buf1, buf2);
        case 26:
            return memcmp_fixed<26>(buf1, buf2);
        case 27:
            return memcmp_fixed<27>(buf1, buf2);
        case 28:
            return memcmp_fixed<28>(buf1, buf2);
        case 29:
            return memcmp_fixed<29>(buf1, buf2);
        case 30:
            return memcmp_fixed<30>(buf1, buf2);
        case 31:
            return memcmp_fixed<31>(buf1, buf2);
        case 32:
            return memcmp_fixed<32>(buf1, buf2);
        case 33:
            return memcmp_fixed<33>(buf1, buf2);
        case 34:
            return memcmp_fixed<34>(buf1, buf2);
        case 35:
            return memcmp_fixed<35>(buf1, buf2);
        case 36:
            return memcmp_fixed<36>(buf1, buf2);
        case 37:
            return memcmp_fixed<37>(buf1, buf2);
        case 38:
            return memcmp_fixed<38>(buf1, buf2);
        case 39:
            return memcmp_fixed<39>(buf1, buf2);
        case 40:
            return memcmp_fixed<40>(buf1, buf2);
        case 41:
            return memcmp_fixed<41>(buf1, buf2);
        case 42:
            return memcmp_fixed<42>(buf1, buf2);
        case 43:
            return memcmp_fixed<43>(buf1, buf2);
        case 44:
            return memcmp_fixed<44>(buf1, buf2);
        case 45:
            return memcmp_fixed<45>(buf1, buf2);
        case 46:
            return memcmp_fixed<46>(buf1, buf2);
        case 47:
            return memcmp_fixed<47>(buf1, buf2);
        case 48:
            return memcmp_fixed<48>(buf1, buf2);
        case 49:
            return memcmp_fixed<49>(buf1, buf2);
        case 50:
            return memcmp_fixed<50>(buf1, buf2);
        case 51:
            return memcmp_fixed<51>(buf1, buf2);
        case 52:
            return memcmp_fixed<52>(buf1, buf2);
        case 53:
            return memcmp_fixed<53>(buf1, buf2);
        case 54:
            return memcmp_fixed<54>(buf1, buf2);
        case 55:
            return memcmp_fixed<55>(buf1, buf2);
        case 56:
            return memcmp_fixed<56>(buf1, buf2);
        case 57:
            return memcmp_fixed<57>(buf1, buf2);
        case 58:
            return memcmp_fixed<58>(buf1, buf2);
        case 59:
            return memcmp_fixed<59>(buf1, buf2);
        case 60:
            return memcmp_fixed<60>(buf1, buf2);
        case 61:
            return memcmp_fixed<61>(buf1, buf2);
        case 62:
            return memcmp_fixed<62>(buf1, buf2);
        case 63:
            return memcmp_fixed<63>(buf1, buf2);
        case 64:
            return memcmp_fixed<64>(buf1, buf2);
        case 65:
            return memcmp_fixed<65>(buf1, buf2);
        case 66:
            return memcmp_fixed<66>(buf1, buf2);
        case 67:
            return memcmp_fixed<67>(buf1, buf2);
        case 68:
            return memcmp_fixed<68>(buf1, buf2);
        case 69:
            return memcmp_fixed<69>(buf1, buf2);
        case 70:
            return memcmp_fixed<70>(buf1, buf2);
        case 71:
            return memcmp_fixed<71>(buf1, buf2);
        case 72:
            return memcmp_fixed<72>(buf1, buf2);
        case 73:
            return memcmp_fixed<73>(buf1, buf2);
        case 74:
            return memcmp_fixed<74>(buf1, buf2);
        case 75:
            return memcmp_fixed<75>(buf1, buf2);
        case 76:
            return memcmp_fixed<76>(buf1, buf2);
        case 77:
            return memcmp_fixed<77>(buf1, buf2);
        case 78:
            return memcmp_fixed<78>(buf1, buf2);
        case 79:
            return memcmp_fixed<79>(buf1, buf2);
        case 80:
            return memcmp_fixed<80>(buf1, buf2);
        case 81:
            return memcmp_fixed<81>(buf1, buf2);
        case 82:
            return memcmp_fixed<82>(buf1, buf2);
        case 83:
            return memcmp_fixed<83>(buf1, buf2);
        case 84:
            return memcmp_fixed<84>(buf1, buf2);
        case 85:
            return memcmp_fixed<85>(buf1, buf2);
        case 86:
            return memcmp_fixed<86>(buf1, buf2);
        case 87:
            return memcmp_fixed<87>(buf1, buf2);
        case 88:
            return memcmp_fixed<88>(buf1, buf2);
        case 89:
            return memcmp_fixed<89>(buf1, buf2);
        case 90:
            return memcmp_fixed<90>(buf1, buf2);
        case 91:
            return memcmp_fixed<91>(buf1, buf2);
        case 92:
            return memcmp_fixed<92>(buf1, buf2);
        case 93:
            return memcmp_fixed<93>(buf1, buf2);
        case 94:
            return memcmp_fixed<94>(buf1, buf2);
        case 95:
            return memcmp_fixed<95>(buf1, buf2);
        case 96:
            return memcmp_fixed<96>(buf1, buf2);
        case 97:
            return memcmp_fixed<97>(buf1, buf2);
        case 98:
            return memcmp_fixed<98>(buf1, buf2);
        case 99:
            return memcmp_fixed<99>(buf1, buf2);
        case 100:
            return memcmp_fixed<100>(buf1, buf2);
        case 101:
            return memcmp_fixed<101>(buf1, buf2);
        case 102:
            return memcmp_fixed<102>(buf1, buf2);
        case 103:
            return memcmp_fixed<103>(buf1, buf2);
        case 104:
            return memcmp_fixed<104>(buf1, buf2);
        case 105:
            return memcmp_fixed<105>(buf1, buf2);
        case 106:
            return memcmp_fixed<106>(buf1, buf2);
        case 107:
            return memcmp_fixed<107>(buf1, buf2);
        case 108:
            return memcmp_fixed<108>(buf1, buf2);
        case 109:
            return memcmp_fixed<109>(buf1, buf2);
        case 110:
            return memcmp_fixed<110>(buf1, buf2);
        case 111:
            return memcmp_fixed<111>(buf1, buf2);
        case 112:
            return memcmp_fixed<112>(buf1, buf2);
        case 113:
            return memcmp_fixed<113>(buf1, buf2);
        case 114:
            return memcmp_fixed<114>(buf1, buf2);
        case 115:
            return memcmp_fixed<115>(buf1, buf2);
        case 116:
            return memcmp_fixed<116>(buf1, buf2);
        case 117:
            return memcmp_fixed<117>(buf1, buf2);
        case 118:
            return memcmp_fixed<118>(buf1, buf2);
        case 119:
            return memcmp_fixed<119>(buf1, buf2);
        case 120:
            return memcmp_fixed<120>(buf1, buf2);
        case 121:
            return memcmp_fixed<121>(buf1, buf2);
        case 122:
            return memcmp_fixed<122>(buf1, buf2);
        case 123:
            return memcmp_fixed<123>(buf1, buf2);
        case 124:
            return memcmp_fixed<124>(buf1, buf2);
        case 125:
            return memcmp_fixed<125>(buf1, buf2);
        case 126:
            return memcmp_fixed<126>(buf1, buf2);
        case 127:
            return memcmp_fixed<127>(buf1, buf2);
        case 128:
            return memcmp_fixed<128>(buf1, buf2);
        case 129:
            return memcmp_fixed<129>(buf1, buf2);
        case 130:
            return memcmp_fixed<130>(buf1, buf2);
        case 131:
            return memcmp_fixed<131>(buf1, buf2);
        case 132:
            return memcmp_fixed<132>(buf1, buf2);
        case 133:
            return memcmp_fixed<133>(buf1, buf2);
        case 134:
            return memcmp_fixed<134>(buf1, buf2);
        case 135:
            return memcmp_fixed<135>(buf1, buf2);
        case 136:
            return memcmp_fixed<136>(buf1, buf2);
        case 137:
            return memcmp_fixed<137>(buf1, buf2);
        case 138:
            return memcmp_fixed<138>(buf1, buf2);
        case 139:
            return memcmp_fixed<139>(buf1, buf2);
        case 140:
            return memcmp_fixed<140>(buf1, buf2);
        case 141:
            return memcmp_fixed<141>(buf1, buf2);
        case 142:
            return memcmp_fixed<142>(buf1, buf2);
        case 143:
            return memcmp_fixed<143>(buf1, buf2);
        case 144:
            return memcmp_fixed<144>(buf1, buf2);
        case 145:
            return memcmp_fixed<145>(buf1, buf2);
        case 146:
            return memcmp_fixed<146>(buf1, buf2);
        case 147:
            return memcmp_fixed<147>(buf1, buf2);
        case 148:
            return memcmp_fixed<148>(buf1, buf2);
        case 149:
            return memcmp_fixed<149>(buf1, buf2);
        case 150:
            return memcmp_fixed<150>(buf1, buf2);
        case 151:
            return memcmp_fixed<151>(buf1, buf2);
        case 152:
            return memcmp_fixed<152>(buf1, buf2);
        case 153:
            return memcmp_fixed<153>(buf1, buf2);
        case 154:
            return memcmp_fixed<154>(buf1, buf2);
        case 155:
            return memcmp_fixed<155>(buf1, buf2);
        case 156:
            return memcmp_fixed<156>(buf1, buf2);
        case 157:
            return memcmp_fixed<157>(buf1, buf2);
        case 158:
            return memcmp_fixed<158>(buf1, buf2);
        case 159:
            return memcmp_fixed<159>(buf1, buf2);
        case 160:
            return memcmp_fixed<160>(buf1, buf2);
        case 161:
            return memcmp_fixed<161>(buf1, buf2);
        case 162:
            return memcmp_fixed<162>(buf1, buf2);
        case 163:
            return memcmp_fixed<163>(buf1, buf2);
        case 164:
            return memcmp_fixed<164>(buf1, buf2);
        case 165:
            return memcmp_fixed<165>(buf1, buf2);
        case 166:
            return memcmp_fixed<166>(buf1, buf2);
        case 167:
            return memcmp_fixed<167>(buf1, buf2);
        case 168:
            return memcmp_fixed<168>(buf1, buf2);
        case 169:
            return memcmp_fixed<169>(buf1, buf2);
        case 170:
            return memcmp_fixed<170>(buf1, buf2);
        case 171:
            return memcmp_fixed<171>(buf1, buf2);
        case 172:
            return memcmp_fixed<172>(buf1, buf2);
        case 173:
            return memcmp_fixed<173>(buf1, buf2);
        case 174:
            return memcmp_fixed<174>(buf1, buf2);
        case 175:
            return memcmp_fixed<175>(buf1, buf2);
        case 176:
            return memcmp_fixed<176>(buf1, buf2);
        case 177:
            return memcmp_fixed<177>(buf1, buf2);
        case 178:
            return memcmp_fixed<178>(buf1, buf2);
        case 179:
            return memcmp_fixed<179>(buf1, buf2);
        case 180:
            return memcmp_fixed<180>(buf1, buf2);
        case 181:
            return memcmp_fixed<181>(buf1, buf2);
        case 182:
            return memcmp_fixed<182>(buf1, buf2);
        case 183:
            return memcmp_fixed<183>(buf1, buf2);
        case 184:
            return memcmp_fixed<184>(buf1, buf2);
        case 185:
            return memcmp_fixed<185>(buf1, buf2);
        case 186:
            return memcmp_fixed<186>(buf1, buf2);
        case 187:
            return memcmp_fixed<187>(buf1, buf2);
        case 188:
            return memcmp_fixed<188>(buf1, buf2);
        case 189:
            return memcmp_fixed<189>(buf1, buf2);
        case 190:
            return memcmp_fixed<190>(buf1, buf2);
        case 191:
            return memcmp_fixed<191>(buf1, buf2);
        case 192:
            return memcmp_fixed<192>(buf1, buf2);
        case 193:
            return memcmp_fixed<193>(buf1, buf2);
        case 194:
            return memcmp_fixed<194>(buf1, buf2);
        case 195:
            return memcmp_fixed<195>(buf1, buf2);
        case 196:
            return memcmp_fixed<196>(buf1, buf2);
        case 197:
            return memcmp_fixed<197>(buf1, buf2);
        case 198:
            return memcmp_fixed<198>(buf1, buf2);
        case 199:
            return memcmp_fixed<199>(buf1, buf2);
        case 200:
            return memcmp_fixed<200>(buf1, buf2);
        case 201:
            return memcmp_fixed<201>(buf1, buf2);
        case 202:
            return memcmp_fixed<202>(buf1, buf2);
        case 203:
            return memcmp_fixed<203>(buf1, buf2);
        case 204:
            return memcmp_fixed<204>(buf1, buf2);
        case 205:
            return memcmp_fixed<205>(buf1, buf2);
        case 206:
            return memcmp_fixed<206>(buf1, buf2);
        case 207:
            return memcmp_fixed<207>(buf1, buf2);
        case 208:
            return memcmp_fixed<208>(buf1, buf2);
        case 209:
            return memcmp_fixed<209>(buf1, buf2);
        case 210:
            return memcmp_fixed<210>(buf1, buf2);
        case 211:
            return memcmp_fixed<211>(buf1, buf2);
        case 212:
            return memcmp_fixed<212>(buf1, buf2);
        case 213:
            return memcmp_fixed<213>(buf1, buf2);
        case 214:
            return memcmp_fixed<214>(buf1, buf2);
        case 215:
            return memcmp_fixed<215>(buf1, buf2);
        case 216:
            return memcmp_fixed<216>(buf1, buf2);
        case 217:
            return memcmp_fixed<217>(buf1, buf2);
        case 218:
            return memcmp_fixed<218>(buf1, buf2);
        case 219:
            return memcmp_fixed<219>(buf1, buf2);
        case 220:
            return memcmp_fixed<220>(buf1, buf2);
        case 221:
            return memcmp_fixed<221>(buf1, buf2);
        case 222:
            return memcmp_fixed<222>(buf1, buf2);
        case 223:
            return memcmp_fixed<223>(buf1, buf2);
        case 224:
            return memcmp_fixed<224>(buf1, buf2);
        case 225:
            return memcmp_fixed<225>(buf1, buf2);
        case 226:
            return memcmp_fixed<226>(buf1, buf2);
        case 227:
            return memcmp_fixed<227>(buf1, buf2);
        case 228:
            return memcmp_fixed<228>(buf1, buf2);
        case 229:
            return memcmp_fixed<229>(buf1, buf2);
        case 230:
            return memcmp_fixed<230>(buf1, buf2);
        case 231:
            return memcmp_fixed<231>(buf1, buf2);
        case 232:
            return memcmp_fixed<232>(buf1, buf2);
        case 233:
            return memcmp_fixed<233>(buf1, buf2);
        case 234:
            return memcmp_fixed<234>(buf1, buf2);
        case 235:
            return memcmp_fixed<235>(buf1, buf2);
        case 236:
            return memcmp_fixed<236>(buf1, buf2);
        case 237:
            return memcmp_fixed<237>(buf1, buf2);
        case 238:
            return memcmp_fixed<238>(buf1, buf2);
        case 239:
            return memcmp_fixed<239>(buf1, buf2);
        case 240:
            return memcmp_fixed<240>(buf1, buf2);
        case 241:
            return memcmp_fixed<241>(buf1, buf2);
        case 242:
            return memcmp_fixed<242>(buf1, buf2);
        case 243:
            return memcmp_fixed<243>(buf1, buf2);
        case 244:
            return memcmp_fixed<244>(buf1, buf2);
        case 245:
            return memcmp_fixed<245>(buf1, buf2);
        case 246:
            return memcmp_fixed<246>(buf1, buf2);
        case 247:
            return memcmp_fixed<247>(buf1, buf2);
        case 248:
            return memcmp_fixed<248>(buf1, buf2);
        case 249:
            return memcmp_fixed<249>(buf1, buf2);
        case 250:
            return memcmp_fixed<250>(buf1, buf2);
        case 251:
            return memcmp_fixed<251>(buf1, buf2);
        case 252:
            return memcmp_fixed<252>(buf1, buf2);
        case 253:
            return memcmp_fixed<253>(buf1, buf2);
        case 254:
            return memcmp_fixed<254>(buf1, buf2);
        case 255:
            return memcmp_fixed<255>(buf1, buf2);
        case 256:
            return memcmp_fixed<256>(buf1, buf2);
        default:
            return std::memcmp(buf1, buf2, size);
        }
    }

    inline void fast_memset(void* dest, const int value, const std::size_t size) {
        switch (size) {
        case 0:
            return;
        case 1:
            return memset_fixed<1>(dest, value);
        case 2:
            return memset_fixed<2>(dest, value);
        case 3:
            return memset_fixed<3>(dest, value);
        case 4:
            return memset_fixed<4>(dest, value);
        case 5:
            return memset_fixed<5>(dest, value);
        case 6:
            return memset_fixed<6>(dest, value);
        case 7:
            return memset_fixed<7>(dest, value);
        case 8:
            return memset_fixed<8>(dest, value);
        case 9:
            return memset_fixed<9>(dest, value);
        case 10:
            return memset_fixed<10>(dest, value);
        case 11:
            return memset_fixed<11>(dest, value);
        case 12:
            return memset_fixed<12>(dest, value);
        case 13:
            return memset_fixed<13>(dest, value);
        case 14:
            return memset_fixed<14>(dest, value);
        case 15:
            return memset_fixed<15>(dest, value);
        case 16:
            return memset_fixed<16>(dest, value);
        case 17:
            return memset_fixed<17>(dest, value);
        case 18:
            return memset_fixed<18>(dest, value);
        case 19:
            return memset_fixed<19>(dest, value);
        case 20:
            return memset_fixed<20>(dest, value);
        case 21:
            return memset_fixed<21>(dest, value);
        case 22:
            return memset_fixed<22>(dest, value);
        case 23:
            return memset_fixed<23>(dest, value);
        case 24:
            return memset_fixed<24>(dest, value);
        case 25:
            return memset_fixed<25>(dest, value);
        case 26:
            return memset_fixed<26>(dest, value);
        case 27:
            return memset_fixed<27>(dest, value);
        case 28:
            return memset_fixed<28>(dest, value);
        case 29:
            return memset_fixed<29>(dest, value);
        case 30:
            return memset_fixed<30>(dest, value);
        case 31:
            return memset_fixed<31>(dest, value);
        case 32:
            return memset_fixed<32>(dest, value);
        case 33:
            return memset_fixed<33>(dest, value);
        case 34:
            return memset_fixed<34>(dest, value);
        case 35:
            return memset_fixed<35>(dest, value);
        case 36:
            return memset_fixed<36>(dest, value);
        case 37:
            return memset_fixed<37>(dest, value);
        case 38:
            return memset_fixed<38>(dest, value);
        case 39:
            return memset_fixed<39>(dest, value);
        case 40:
            return memset_fixed<40>(dest, value);
        case 41:
            return memset_fixed<41>(dest, value);
        case 42:
            return memset_fixed<42>(dest, value);
        case 43:
            return memset_fixed<43>(dest, value);
        case 44:
            return memset_fixed<44>(dest, value);
        case 45:
            return memset_fixed<45>(dest, value);
        case 46:
            return memset_fixed<46>(dest, value);
        case 47:
            return memset_fixed<47>(dest, value);
        case 48:
            return memset_fixed<48>(dest, value);
        case 49:
            return memset_fixed<49>(dest, value);
        case 50:
            return memset_fixed<50>(dest, value);
        case 51:
            return memset_fixed<51>(dest, value);
        case 52:
            return memset_fixed<52>(dest, value);
        case 53:
            return memset_fixed<53>(dest, value);
        case 54:
            return memset_fixed<54>(dest, value);
        case 55:
            return memset_fixed<55>(dest, value);
        case 56:
            return memset_fixed<56>(dest, value);
        case 57:
            return memset_fixed<57>(dest, value);
        case 58:
            return memset_fixed<58>(dest, value);
        case 59:
            return memset_fixed<59>(dest, value);
        case 60:
            return memset_fixed<60>(dest, value);
        case 61:
            return memset_fixed<61>(dest, value);
        case 62:
            return memset_fixed<62>(dest, value);
        case 63:
            return memset_fixed<63>(dest, value);
        case 64:
            return memset_fixed<64>(dest, value);
        case 65:
            return memset_fixed<65>(dest, value);
        case 66:
            return memset_fixed<66>(dest, value);
        case 67:
            return memset_fixed<67>(dest, value);
        case 68:
            return memset_fixed<68>(dest, value);
        case 69:
            return memset_fixed<69>(dest, value);
        case 70:
            return memset_fixed<70>(dest, value);
        case 71:
            return memset_fixed<71>(dest, value);
        case 72:
            return memset_fixed<72>(dest, value);
        case 73:
            return memset_fixed<73>(dest, value);
        case 74:
            return memset_fixed<74>(dest, value);
        case 75:
            return memset_fixed<75>(dest, value);
        case 76:
            return memset_fixed<76>(dest, value);
        case 77:
            return memset_fixed<77>(dest, value);
        case 78:
            return memset_fixed<78>(dest, value);
        case 79:
            return memset_fixed<79>(dest, value);
        case 80:
            return memset_fixed<80>(dest, value);
        case 81:
            return memset_fixed<81>(dest, value);
        case 82:
            return memset_fixed<82>(dest, value);
        case 83:
            return memset_fixed<83>(dest, value);
        case 84:
            return memset_fixed<84>(dest, value);
        case 85:
            return memset_fixed<85>(dest, value);
        case 86:
            return memset_fixed<86>(dest, value);
        case 87:
            return memset_fixed<87>(dest, value);
        case 88:
            return memset_fixed<88>(dest, value);
        case 89:
            return memset_fixed<89>(dest, value);
        case 90:
            return memset_fixed<90>(dest, value);
        case 91:
            return memset_fixed<91>(dest, value);
        case 92:
            return memset_fixed<92>(dest, value);
        case 93:
            return memset_fixed<93>(dest, value);
        case 94:
            return memset_fixed<94>(dest, value);
        case 95:
            return memset_fixed<95>(dest, value);
        case 96:
            return memset_fixed<96>(dest, value);
        case 97:
            return memset_fixed<97>(dest, value);
        case 98:
            return memset_fixed<98>(dest, value);
        case 99:
            return memset_fixed<99>(dest, value);
        case 100:
            return memset_fixed<100>(dest, value);
        case 101:
            return memset_fixed<101>(dest, value);
        case 102:
            return memset_fixed<102>(dest, value);
        case 103:
            return memset_fixed<103>(dest, value);
        case 104:
            return memset_fixed<104>(dest, value);
        case 105:
            return memset_fixed<105>(dest, value);
        case 106:
            return memset_fixed<106>(dest, value);
        case 107:
            return memset_fixed<107>(dest, value);
        case 108:
            return memset_fixed<108>(dest, value);
        case 109:
            return memset_fixed<109>(dest, value);
        case 110:
            return memset_fixed<110>(dest, value);
        case 111:
            return memset_fixed<111>(dest, value);
        case 112:
            return memset_fixed<112>(dest, value);
        case 113:
            return memset_fixed<113>(dest, value);
        case 114:
            return memset_fixed<114>(dest, value);
        case 115:
            return memset_fixed<115>(dest, value);
        case 116:
            return memset_fixed<116>(dest, value);
        case 117:
            return memset_fixed<117>(dest, value);
        case 118:
            return memset_fixed<118>(dest, value);
        case 119:
            return memset_fixed<119>(dest, value);
        case 120:
            return memset_fixed<120>(dest, value);
        case 121:
            return memset_fixed<121>(dest, value);
        case 122:
            return memset_fixed<122>(dest, value);
        case 123:
            return memset_fixed<123>(dest, value);
        case 124:
            return memset_fixed<124>(dest, value);
        case 125:
            return memset_fixed<125>(dest, value);
        case 126:
            return memset_fixed<126>(dest, value);
        case 127:
            return memset_fixed<127>(dest, value);
        case 128:
            return memset_fixed<128>(dest, value);
        case 129:
            return memset_fixed<129>(dest, value);
        case 130:
            return memset_fixed<130>(dest, value);
        case 131:
            return memset_fixed<131>(dest, value);
        case 132:
            return memset_fixed<132>(dest, value);
        case 133:
            return memset_fixed<133>(dest, value);
        case 134:
            return memset_fixed<134>(dest, value);
        case 135:
            return memset_fixed<135>(dest, value);
        case 136:
            return memset_fixed<136>(dest, value);
        case 137:
            return memset_fixed<137>(dest, value);
        case 138:
            return memset_fixed<138>(dest, value);
        case 139:
            return memset_fixed<139>(dest, value);
        case 140:
            return memset_fixed<140>(dest, value);
        case 141:
            return memset_fixed<141>(dest, value);
        case 142:
            return memset_fixed<142>(dest, value);
        case 143:
            return memset_fixed<143>(dest, value);
        case 144:
            return memset_fixed<144>(dest, value);
        case 145:
            return memset_fixed<145>(dest, value);
        case 146:
            return memset_fixed<146>(dest, value);
        case 147:
            return memset_fixed<147>(dest, value);
        case 148:
            return memset_fixed<148>(dest, value);
        case 149:
            return memset_fixed<149>(dest, value);
        case 150:
            return memset_fixed<150>(dest, value);
        case 151:
            return memset_fixed<151>(dest, value);
        case 152:
            return memset_fixed<152>(dest, value);
        case 153:
            return memset_fixed<153>(dest, value);
        case 154:
            return memset_fixed<154>(dest, value);
        case 155:
            return memset_fixed<155>(dest, value);
        case 156:
            return memset_fixed<156>(dest, value);
        case 157:
            return memset_fixed<157>(dest, value);
        case 158:
            return memset_fixed<158>(dest, value);
        case 159:
            return memset_fixed<159>(dest, value);
        case 160:
            return memset_fixed<160>(dest, value);
        case 161:
            return memset_fixed<161>(dest, value);
        case 162:
            return memset_fixed<162>(dest, value);
        case 163:
            return memset_fixed<163>(dest, value);
        case 164:
            return memset_fixed<164>(dest, value);
        case 165:
            return memset_fixed<165>(dest, value);
        case 166:
            return memset_fixed<166>(dest, value);
        case 167:
            return memset_fixed<167>(dest, value);
        case 168:
            return memset_fixed<168>(dest, value);
        case 169:
            return memset_fixed<169>(dest, value);
        case 170:
            return memset_fixed<170>(dest, value);
        case 171:
            return memset_fixed<171>(dest, value);
        case 172:
            return memset_fixed<172>(dest, value);
        case 173:
            return memset_fixed<173>(dest, value);
        case 174:
            return memset_fixed<174>(dest, value);
        case 175:
            return memset_fixed<175>(dest, value);
        case 176:
            return memset_fixed<176>(dest, value);
        case 177:
            return memset_fixed<177>(dest, value);
        case 178:
            return memset_fixed<178>(dest, value);
        case 179:
            return memset_fixed<179>(dest, value);
        case 180:
            return memset_fixed<180>(dest, value);
        case 181:
            return memset_fixed<181>(dest, value);
        case 182:
            return memset_fixed<182>(dest, value);
        case 183:
            return memset_fixed<183>(dest, value);
        case 184:
            return memset_fixed<184>(dest, value);
        case 185:
            return memset_fixed<185>(dest, value);
        case 186:
            return memset_fixed<186>(dest, value);
        case 187:
            return memset_fixed<187>(dest, value);
        case 188:
            return memset_fixed<188>(dest, value);
        case 189:
            return memset_fixed<189>(dest, value);
        case 190:
            return memset_fixed<190>(dest, value);
        case 191:
            return memset_fixed<191>(dest, value);
        case 192:
            return memset_fixed<192>(dest, value);
        case 193:
            return memset_fixed<193>(dest, value);
        case 194:
            return memset_fixed<194>(dest, value);
        case 195:
            return memset_fixed<195>(dest, value);
        case 196:
            return memset_fixed<196>(dest, value);
        case 197:
            return memset_fixed<197>(dest, value);
        case 198:
            return memset_fixed<198>(dest, value);
        case 199:
            return memset_fixed<199>(dest, value);
        case 200:
            return memset_fixed<200>(dest, value);
        case 201:
            return memset_fixed<201>(dest, value);
        case 202:
            return memset_fixed<202>(dest, value);
        case 203:
            return memset_fixed<203>(dest, value);
        case 204:
            return memset_fixed<204>(dest, value);
        case 205:
            return memset_fixed<205>(dest, value);
        case 206:
            return memset_fixed<206>(dest, value);
        case 207:
            return memset_fixed<207>(dest, value);
        case 208:
            return memset_fixed<208>(dest, value);
        case 209:
            return memset_fixed<209>(dest, value);
        case 210:
            return memset_fixed<210>(dest, value);
        case 211:
            return memset_fixed<211>(dest, value);
        case 212:
            return memset_fixed<212>(dest, value);
        case 213:
            return memset_fixed<213>(dest, value);
        case 214:
            return memset_fixed<214>(dest, value);
        case 215:
            return memset_fixed<215>(dest, value);
        case 216:
            return memset_fixed<216>(dest, value);
        case 217:
            return memset_fixed<217>(dest, value);
        case 218:
            return memset_fixed<218>(dest, value);
        case 219:
            return memset_fixed<219>(dest, value);
        case 220:
            return memset_fixed<220>(dest, value);
        case 221:
            return memset_fixed<221>(dest, value);
        case 222:
            return memset_fixed<222>(dest, value);
        case 223:
            return memset_fixed<223>(dest, value);
        case 224:
            return memset_fixed<224>(dest, value);
        case 225:
            return memset_fixed<225>(dest, value);
        case 226:
            return memset_fixed<226>(dest, value);
        case 227:
            return memset_fixed<227>(dest, value);
        case 228:
            return memset_fixed<228>(dest, value);
        case 229:
            return memset_fixed<229>(dest, value);
        case 230:
            return memset_fixed<230>(dest, value);
        case 231:
            return memset_fixed<231>(dest, value);
        case 232:
            return memset_fixed<232>(dest, value);
        case 233:
            return memset_fixed<233>(dest, value);
        case 234:
            return memset_fixed<234>(dest, value);
        case 235:
            return memset_fixed<235>(dest, value);
        case 236:
            return memset_fixed<236>(dest, value);
        case 237:
            return memset_fixed<237>(dest, value);
        case 238:
            return memset_fixed<238>(dest, value);
        case 239:
            return memset_fixed<239>(dest, value);
        case 240:
            return memset_fixed<240>(dest, value);
        case 241:
            return memset_fixed<241>(dest, value);
        case 242:
            return memset_fixed<242>(dest, value);
        case 243:
            return memset_fixed<243>(dest, value);
        case 244:
            return memset_fixed<244>(dest, value);
        case 245:
            return memset_fixed<245>(dest, value);
        case 246:
            return memset_fixed<246>(dest, value);
        case 247:
            return memset_fixed<247>(dest, value);
        case 248:
            return memset_fixed<248>(dest, value);
        case 249:
            return memset_fixed<249>(dest, value);
        case 250:
            return memset_fixed<250>(dest, value);
        case 251:
            return memset_fixed<251>(dest, value);
        case 252:
            return memset_fixed<252>(dest, value);
        case 253:
            return memset_fixed<253>(dest, value);
        case 254:
            return memset_fixed<254>(dest, value);
        case 255:
            return memset_fixed<255>(dest, value);
        case 256:
            return memset_fixed<256>(dest, value);
        default:
            std::memset(dest, value, size);
        }
    }

    [[nodiscard]] inline void* fast_memmove(void* dest, const void* src, const std::size_t count) {
        switch (count) {
        case 0:
            return dest;
        case 1:
            return memmove_fixed<1>(dest, src);
        case 2:
            return memmove_fixed<2>(dest, src);
        case 3:
            return memmove_fixed<3>(dest, src);
        case 4:
            return memmove_fixed<4>(dest, src);
        case 5:
            return memmove_fixed<5>(dest, src);
        case 6:
            return memmove_fixed<6>(dest, src);
        case 7:
            return memmove_fixed<7>(dest, src);
        case 8:
            return memmove_fixed<8>(dest, src);
        case 9:
            return memmove_fixed<9>(dest, src);
        case 10:
            return memmove_fixed<10>(dest, src);
        case 11:
            return memmove_fixed<11>(dest, src);
        case 12:
            return memmove_fixed<12>(dest, src);
        case 13:
            return memmove_fixed<13>(dest, src);
        case 14:
            return memmove_fixed<14>(dest, src);
        case 15:
            return memmove_fixed<15>(dest, src);
        case 16:
            return memmove_fixed<16>(dest, src);
        case 17:
            return memmove_fixed<17>(dest, src);
        case 18:
            return memmove_fixed<18>(dest, src);
        case 19:
            return memmove_fixed<19>(dest, src);
        case 20:
            return memmove_fixed<20>(dest, src);
        case 21:
            return memmove_fixed<21>(dest, src);
        case 22:
            return memmove_fixed<22>(dest, src);
        case 23:
            return memmove_fixed<23>(dest, src);
        case 24:
            return memmove_fixed<24>(dest, src);
        case 25:
            return memmove_fixed<25>(dest, src);
        case 26:
            return memmove_fixed<26>(dest, src);
        case 27:
            return memmove_fixed<27>(dest, src);
        case 28:
            return memmove_fixed<28>(dest, src);
        case 29:
            return memmove_fixed<29>(dest, src);
        case 30:
            return memmove_fixed<30>(dest, src);
        case 31:
            return memmove_fixed<31>(dest, src);
        case 32:
            return memmove_fixed<32>(dest, src);
        case 33:
            return memmove_fixed<33>(dest, src);
        case 34:
            return memmove_fixed<34>(dest, src);
        case 35:
            return memmove_fixed<35>(dest, src);
        case 36:
            return memmove_fixed<36>(dest, src);
        case 37:
            return memmove_fixed<37>(dest, src);
        case 38:
            return memmove_fixed<38>(dest, src);
        case 39:
            return memmove_fixed<39>(dest, src);
        case 40:
            return memmove_fixed<40>(dest, src);
        case 41:
            return memmove_fixed<41>(dest, src);
        case 42:
            return memmove_fixed<42>(dest, src);
        case 43:
            return memmove_fixed<43>(dest, src);
        case 44:
            return memmove_fixed<44>(dest, src);
        case 45:
            return memmove_fixed<45>(dest, src);
        case 46:
            return memmove_fixed<46>(dest, src);
        case 47:
            return memmove_fixed<47>(dest, src);
        case 48:
            return memmove_fixed<48>(dest, src);
        case 49:
            return memmove_fixed<49>(dest, src);
        case 50:
            return memmove_fixed<50>(dest, src);
        case 51:
            return memmove_fixed<51>(dest, src);
        case 52:
            return memmove_fixed<52>(dest, src);
        case 53:
            return memmove_fixed<53>(dest, src);
        case 54:
            return memmove_fixed<54>(dest, src);
        case 55:
            return memmove_fixed<55>(dest, src);
        case 56:
            return memmove_fixed<56>(dest, src);
        case 57:
            return memmove_fixed<57>(dest, src);
        case 58:
            return memmove_fixed<58>(dest, src);
        case 59:
            return memmove_fixed<59>(dest, src);
        case 60:
            return memmove_fixed<60>(dest, src);
        case 61:
            return memmove_fixed<61>(dest, src);
        case 62:
            return memmove_fixed<62>(dest, src);
        case 63:
            return memmove_fixed<63>(dest, src);
        case 64:
            return memmove_fixed<64>(dest, src);
        case 65:
            return memmove_fixed<65>(dest, src);
        case 66:
            return memmove_fixed<66>(dest, src);
        case 67:
            return memmove_fixed<67>(dest, src);
        case 68:
            return memmove_fixed<68>(dest, src);
        case 69:
            return memmove_fixed<69>(dest, src);
        case 70:
            return memmove_fixed<70>(dest, src);
        case 71:
            return memmove_fixed<71>(dest, src);
        case 72:
            return memmove_fixed<72>(dest, src);
        case 73:
            return memmove_fixed<73>(dest, src);
        case 74:
            return memmove_fixed<74>(dest, src);
        case 75:
            return memmove_fixed<75>(dest, src);
        case 76:
            return memmove_fixed<76>(dest, src);
        case 77:
            return memmove_fixed<77>(dest, src);
        case 78:
            return memmove_fixed<78>(dest, src);
        case 79:
            return memmove_fixed<79>(dest, src);
        case 80:
            return memmove_fixed<80>(dest, src);
        case 81:
            return memmove_fixed<81>(dest, src);
        case 82:
            return memmove_fixed<82>(dest, src);
        case 83:
            return memmove_fixed<83>(dest, src);
        case 84:
            return memmove_fixed<84>(dest, src);
        case 85:
            return memmove_fixed<85>(dest, src);
        case 86:
            return memmove_fixed<86>(dest, src);
        case 87:
            return memmove_fixed<87>(dest, src);
        case 88:
            return memmove_fixed<88>(dest, src);
        case 89:
            return memmove_fixed<89>(dest, src);
        case 90:
            return memmove_fixed<90>(dest, src);
        case 91:
            return memmove_fixed<91>(dest, src);
        case 92:
            return memmove_fixed<92>(dest, src);
        case 93:
            return memmove_fixed<93>(dest, src);
        case 94:
            return memmove_fixed<94>(dest, src);
        case 95:
            return memmove_fixed<95>(dest, src);
        case 96:
            return memmove_fixed<96>(dest, src);
        case 97:
            return memmove_fixed<97>(dest, src);
        case 98:
            return memmove_fixed<98>(dest, src);
        case 99:
            return memmove_fixed<99>(dest, src);
        case 100:
            return memmove_fixed<100>(dest, src);
        case 101:
            return memmove_fixed<101>(dest, src);
        case 102:
            return memmove_fixed<102>(dest, src);
        case 103:
            return memmove_fixed<103>(dest, src);
        case 104:
            return memmove_fixed<104>(dest, src);
        case 105:
            return memmove_fixed<105>(dest, src);
        case 106:
            return memmove_fixed<106>(dest, src);
        case 107:
            return memmove_fixed<107>(dest, src);
        case 108:
            return memmove_fixed<108>(dest, src);
        case 109:
            return memmove_fixed<109>(dest, src);
        case 110:
            return memmove_fixed<110>(dest, src);
        case 111:
            return memmove_fixed<111>(dest, src);
        case 112:
            return memmove_fixed<112>(dest, src);
        case 113:
            return memmove_fixed<113>(dest, src);
        case 114:
            return memmove_fixed<114>(dest, src);
        case 115:
            return memmove_fixed<115>(dest, src);
        case 116:
            return memmove_fixed<116>(dest, src);
        case 117:
            return memmove_fixed<117>(dest, src);
        case 118:
            return memmove_fixed<118>(dest, src);
        case 119:
            return memmove_fixed<119>(dest, src);
        case 120:
            return memmove_fixed<120>(dest, src);
        case 121:
            return memmove_fixed<121>(dest, src);
        case 122:
            return memmove_fixed<122>(dest, src);
        case 123:
            return memmove_fixed<123>(dest, src);
        case 124:
            return memmove_fixed<124>(dest, src);
        case 125:
            return memmove_fixed<125>(dest, src);
        case 126:
            return memmove_fixed<126>(dest, src);
        case 127:
            return memmove_fixed<127>(dest, src);
        case 128:
            return memmove_fixed<128>(dest, src);
        case 129:
            return memmove_fixed<129>(dest, src);
        case 130:
            return memmove_fixed<130>(dest, src);
        case 131:
            return memmove_fixed<131>(dest, src);
        case 132:
            return memmove_fixed<132>(dest, src);
        case 133:
            return memmove_fixed<133>(dest, src);
        case 134:
            return memmove_fixed<134>(dest, src);
        case 135:
            return memmove_fixed<135>(dest, src);
        case 136:
            return memmove_fixed<136>(dest, src);
        case 137:
            return memmove_fixed<137>(dest, src);
        case 138:
            return memmove_fixed<138>(dest, src);
        case 139:
            return memmove_fixed<139>(dest, src);
        case 140:
            return memmove_fixed<140>(dest, src);
        case 141:
            return memmove_fixed<141>(dest, src);
        case 142:
            return memmove_fixed<142>(dest, src);
        case 143:
            return memmove_fixed<143>(dest, src);
        case 144:
            return memmove_fixed<144>(dest, src);
        case 145:
            return memmove_fixed<145>(dest, src);
        case 146:
            return memmove_fixed<146>(dest, src);
        case 147:
            return memmove_fixed<147>(dest, src);
        case 148:
            return memmove_fixed<148>(dest, src);
        case 149:
            return memmove_fixed<149>(dest, src);
        case 150:
            return memmove_fixed<150>(dest, src);
        case 151:
            return memmove_fixed<151>(dest, src);
        case 152:
            return memmove_fixed<152>(dest, src);
        case 153:
            return memmove_fixed<153>(dest, src);
        case 154:
            return memmove_fixed<154>(dest, src);
        case 155:
            return memmove_fixed<155>(dest, src);
        case 156:
            return memmove_fixed<156>(dest, src);
        case 157:
            return memmove_fixed<157>(dest, src);
        case 158:
            return memmove_fixed<158>(dest, src);
        case 159:
            return memmove_fixed<159>(dest, src);
        case 160:
            return memmove_fixed<160>(dest, src);
        case 161:
            return memmove_fixed<161>(dest, src);
        case 162:
            return memmove_fixed<162>(dest, src);
        case 163:
            return memmove_fixed<163>(dest, src);
        case 164:
            return memmove_fixed<164>(dest, src);
        case 165:
            return memmove_fixed<165>(dest, src);
        case 166:
            return memmove_fixed<166>(dest, src);
        case 167:
            return memmove_fixed<167>(dest, src);
        case 168:
            return memmove_fixed<168>(dest, src);
        case 169:
            return memmove_fixed<169>(dest, src);
        case 170:
            return memmove_fixed<170>(dest, src);
        case 171:
            return memmove_fixed<171>(dest, src);
        case 172:
            return memmove_fixed<172>(dest, src);
        case 173:
            return memmove_fixed<173>(dest, src);
        case 174:
            return memmove_fixed<174>(dest, src);
        case 175:
            return memmove_fixed<175>(dest, src);
        case 176:
            return memmove_fixed<176>(dest, src);
        case 177:
            return memmove_fixed<177>(dest, src);
        case 178:
            return memmove_fixed<178>(dest, src);
        case 179:
            return memmove_fixed<179>(dest, src);
        case 180:
            return memmove_fixed<180>(dest, src);
        case 181:
            return memmove_fixed<181>(dest, src);
        case 182:
            return memmove_fixed<182>(dest, src);
        case 183:
            return memmove_fixed<183>(dest, src);
        case 184:
            return memmove_fixed<184>(dest, src);
        case 185:
            return memmove_fixed<185>(dest, src);
        case 186:
            return memmove_fixed<186>(dest, src);
        case 187:
            return memmove_fixed<187>(dest, src);
        case 188:
            return memmove_fixed<188>(dest, src);
        case 189:
            return memmove_fixed<189>(dest, src);
        case 190:
            return memmove_fixed<190>(dest, src);
        case 191:
            return memmove_fixed<191>(dest, src);
        case 192:
            return memmove_fixed<192>(dest, src);
        case 193:
            return memmove_fixed<193>(dest, src);
        case 194:
            return memmove_fixed<194>(dest, src);
        case 195:
            return memmove_fixed<195>(dest, src);
        case 196:
            return memmove_fixed<196>(dest, src);
        case 197:
            return memmove_fixed<197>(dest, src);
        case 198:
            return memmove_fixed<198>(dest, src);
        case 199:
            return memmove_fixed<199>(dest, src);
        case 200:
            return memmove_fixed<200>(dest, src);
        case 201:
            return memmove_fixed<201>(dest, src);
        case 202:
            return memmove_fixed<202>(dest, src);
        case 203:
            return memmove_fixed<203>(dest, src);
        case 204:
            return memmove_fixed<204>(dest, src);
        case 205:
            return memmove_fixed<205>(dest, src);
        case 206:
            return memmove_fixed<206>(dest, src);
        case 207:
            return memmove_fixed<207>(dest, src);
        case 208:
            return memmove_fixed<208>(dest, src);
        case 209:
            return memmove_fixed<209>(dest, src);
        case 210:
            return memmove_fixed<210>(dest, src);
        case 211:
            return memmove_fixed<211>(dest, src);
        case 212:
            return memmove_fixed<212>(dest, src);
        case 213:
            return memmove_fixed<213>(dest, src);
        case 214:
            return memmove_fixed<214>(dest, src);
        case 215:
            return memmove_fixed<215>(dest, src);
        case 216:
            return memmove_fixed<216>(dest, src);
        case 217:
            return memmove_fixed<217>(dest, src);
        case 218:
            return memmove_fixed<218>(dest, src);
        case 219:
            return memmove_fixed<219>(dest, src);
        case 220:
            return memmove_fixed<220>(dest, src);
        case 221:
            return memmove_fixed<221>(dest, src);
        case 222:
            return memmove_fixed<222>(dest, src);
        case 223:
            return memmove_fixed<223>(dest, src);
        case 224:
            return memmove_fixed<224>(dest, src);
        case 225:
            return memmove_fixed<225>(dest, src);
        case 226:
            return memmove_fixed<226>(dest, src);
        case 227:
            return memmove_fixed<227>(dest, src);
        case 228:
            return memmove_fixed<228>(dest, src);
        case 229:
            return memmove_fixed<229>(dest, src);
        case 230:
            return memmove_fixed<230>(dest, src);
        case 231:
            return memmove_fixed<231>(dest, src);
        case 232:
            return memmove_fixed<232>(dest, src);
        case 233:
            return memmove_fixed<233>(dest, src);
        case 234:
            return memmove_fixed<234>(dest, src);
        case 235:
            return memmove_fixed<235>(dest, src);
        case 236:
            return memmove_fixed<236>(dest, src);
        case 237:
            return memmove_fixed<237>(dest, src);
        case 238:
            return memmove_fixed<238>(dest, src);
        case 239:
            return memmove_fixed<239>(dest, src);
        case 240:
            return memmove_fixed<240>(dest, src);
        case 241:
            return memmove_fixed<241>(dest, src);
        case 242:
            return memmove_fixed<242>(dest, src);
        case 243:
            return memmove_fixed<243>(dest, src);
        case 244:
            return memmove_fixed<244>(dest, src);
        case 245:
            return memmove_fixed<245>(dest, src);
        case 246:
            return memmove_fixed<246>(dest, src);
        case 247:
            return memmove_fixed<247>(dest, src);
        case 248:
            return memmove_fixed<248>(dest, src);
        case 249:
            return memmove_fixed<249>(dest, src);
        case 250:
            return memmove_fixed<250>(dest, src);
        case 251:
            return memmove_fixed<251>(dest, src);
        case 252:
            return memmove_fixed<252>(dest, src);
        case 253:
            return memmove_fixed<253>(dest, src);
        case 254:
            return memmove_fixed<254>(dest, src);
        case 255:
            return memmove_fixed<255>(dest, src);
        case 256:
            return memmove_fixed<256>(dest, src);
        default:
            return std::memmove(dest, src, count);
        }
    }
#endif // _DEBUG

} // namespace IOTest::Detail
