project(pcg-engine-combination-generation-tests)

enable_testing()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE 
"src/main.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE pcg-engine-combination-generation)
target_link_libraries(${PROJECT_NAME} PRIVATE gtest)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_test(test_all ${PROJECT_NAME})
