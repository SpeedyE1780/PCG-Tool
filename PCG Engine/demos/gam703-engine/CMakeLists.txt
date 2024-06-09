project(PCG-Demo-GAM703-Engine)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE PCG-Engine-Core)
target_link_libraries(${PROJECT_NAME} PRIVATE game-components)
