cmake_minimum_required(VERSION 3.15.0)

project(UTILS LANGUAGES CXX)


file(GLOB LSB_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h")
file(GLOB LSB_RESOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${LSB_RESOURCE} ${LSB_HEADER})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/header")
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui )







