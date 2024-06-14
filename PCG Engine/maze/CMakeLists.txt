project(PCG-Engine-Maze)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/Maze.cpp"

#HPP
"include/pcg/engine/maze/Maze.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Math)
target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Utility)
