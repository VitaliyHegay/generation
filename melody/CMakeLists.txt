cmake_minimum_required(VERSION 3.5)

project(melody LANGUAGES CXX)


add_subdirectory(TestTask/libs/generator)

add_subdirectory(TestTask/libs/noiseAdder)

add_subdirectory(TestTask/libs/wavwritter)

add_subdirectory(TestTask/libs/wavplay)

add_executable(melody main.cpp)

target_link_libraries(${PROJECT_NAME} generator noiseAdder wavwritter wavplay)
