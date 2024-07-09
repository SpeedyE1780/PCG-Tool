project(pcg-engine-maze-generation-tests)

enable_testing()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE pcg-engine-maze-generation)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)

add_test(test_all ${PROJECT_NAME})
