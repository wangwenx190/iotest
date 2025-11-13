cmake_minimum_required(VERSION 4.0)

project(IOTest LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

if(MSVC)
    set(__var_name CMAKE_CXX_FLAGS_RELEASE)
    string(REGEX REPLACE " [-/]Ob[0-9] " " " ${__var_name} "${${__var_name}}")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

add_executable(${PROJECT_NAME} fast_mem.hpp main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Concurrent)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        UNICODE _UNICODE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        _USE_MATH_DEFINES
    )
endif()
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /utf-8 /Zc:__cplusplus
        $<$<NOT:$<CONFIG:Debug>>:/GT /Gw /Gy /jumptablerdata /Ob3 /Oi /Ot /Oy /Zc:inline
        /Qfast_transcendentals /QIntel-jcc-erratum /Qpar /constexpr:depth4096 /arch:AVX2> # MSVC has no x86_64-v3 specific flag, we use AVX2 instead.
        $<$<AND:$<NOT:$<CONFIG:Debug>>,$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>>:/GA>
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<NOT:$<CONFIG:Debug>>:/OPT:REF /OPT:ICF>
    )
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        _ENABLE_EXTENDED_ALIGNED_STORAGE # STL fixed a bug which breaks binary compatibility, thus need to be enabled manually by defining this.
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<NOT:$<CONFIG:Debug>>:-ffunction-sections -fdata-sections -fconstexpr-depth=4096
        -march=x86-64-v3> # x86_64-v4 is too new. x86_64-v3 is at least 10 years old, should be old enough.
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        -static -Wl,-Bstatic
        $<$<NOT:$<CONFIG:Debug>>:-Wl,--gc-sections>
    )
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
