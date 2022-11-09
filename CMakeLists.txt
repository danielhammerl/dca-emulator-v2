cmake_minimum_required(VERSION 3.23)
project(DcaEmulator VERSION 1.0)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
include(CheckCCompilerFlag)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64)
set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;arm64")
check_c_compiler_flag("-arch arm64" arm64Supported)


IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin" AND arm64Supported MATCHES 1)
    set(CMAKE_OSX_ARCHITECTURES arm64)
ENDIF ()


FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG c1064bae925693667c7a34cad264bd5ea3ece177
)

FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED true)

find_package(SFML 2.6.0 COMPONENTS system window graphics network audio)

IF (WIN32)
    link_directories($ENV{BOOST_LIB})
ELSE()
    find_package(Boost
            1.76.0
            REQUIRED
            COMPONENTS filesystem
            )

ENDIF()

add_executable(DcaEmulator main.cpp src/DcaEmulator.cpp src/DcaEmulator.h src/cli/CLI.cpp src/cli/CLI.h src/GlobalState.h)

IF (WIN32)
    target_include_directories(DcaEmulator PUBLIC $ENV{BOOST_ROOT})
    target_link_libraries(DcaEmulator sfml-graphics sfml-audio sfml-window sfml-system)
    target_link_directories(DcaEmulator PUBLIC $ENV{BOOST_LIB})
    file(COPY ./external_bin/openal32.dll DESTINATION ./)
ELSE()
    target_link_libraries(DcaEmulator sfml-graphics sfml-audio sfml-window sfml-system ${Boost_LIBRARIES})
    target_include_directories(DcaEmulator PUBLIC ${Boost_INCLUDE_DIRS})
ENDIF()

file(COPY ./resources DESTINATION ./)
