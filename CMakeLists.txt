cmake_minimum_required(VERSION 3.30)

project(IOTest LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Concurrent)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        UNICODE _UNICODE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        _USE_MATH_DEFINES
    )
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
