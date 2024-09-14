project(DataEngine)

file(GLOB DataEngine_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB DataEngine_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${DataEngine_HEADER} ${DataEngine_SRC})
target_link_libraries(${PROJECT_NAME}  Encryption  spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)