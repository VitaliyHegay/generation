cmake_minimum_required(VERSION 3.5)

project(melody LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)

add_subdirectory(TestTask/libs/generator)
add_subdirectory(TestTask/libs/noiseAdder)
add_subdirectory(TestTask/libs/wavwritter)
add_subdirectory(TestTask/libs/wavplay)
add_subdirectory(TestTask/libs/iniReader)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} generator noiseAdder wavwritter wavplay iniReader)
