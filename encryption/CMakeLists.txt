project(Encryption)

file(GLOB Encryption_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB Encryption_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${Encryption_HEADER} ${Encryption_SRC})
target_link_libraries(${PROJECT_NAME} cryptopp::cryptopp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)