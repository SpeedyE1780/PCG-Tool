cmake_minimum_required(VERSION 3.27)

project(PCG-Demo-GAM703-Engine)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")

add_subdirectory(engine)
add_subdirectory(pcg-engine-cpp-api)

target_link_libraries(${PROJECT_NAME} PRIVATE pcg-engine-cpp-api)
target_link_libraries(${PROJECT_NAME} PRIVATE game-components)

#add_dependencies(${PROJECT_NAME} copy-files)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>)
