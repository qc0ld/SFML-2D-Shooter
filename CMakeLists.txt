cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Google_test)

find_package(Doxygen)

include_directories(Google_test/googletest/include)
include_directories(Google_test/googlemock/include)

add_executable(lab4 main.cpp unit.cpp items.cpp game.h weapons.cpp weapons.h enemies.cpp
        enemies.h game.cpp test.cpp test.h list.h)
include_directories(SFML/include)

set(SFML_ROOT SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(lab4 ${SFML_LIBRARIES} gtest gtest_main)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()

