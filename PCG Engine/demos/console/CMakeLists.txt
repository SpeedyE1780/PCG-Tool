project(PCG-Demo-Console)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE PCG-Engine-Core)
