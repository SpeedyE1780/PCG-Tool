project(pcg-engine-cpp-api)

find_library(pcg-engine-cpp-api-prebuilt irrKlang ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-cpp-api})

