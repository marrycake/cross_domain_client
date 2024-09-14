project(FrameWork)

file(GLOB FrameWork_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB FrameWork_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${FrameWork_HEADER} ${FrameWork_SRC})
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)