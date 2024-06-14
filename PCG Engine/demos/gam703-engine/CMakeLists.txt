project(PCG-Demo-GAM703-Engine)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE PCG-Engine-CPP-API)
target_link_libraries(${PROJECT_NAME} PRIVATE game-components)

add_dependencies(${PROJECT_NAME} copy-files)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>)
