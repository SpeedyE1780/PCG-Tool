project(PCG-Engine-Maze)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/AldousBroder.cpp"
"src/BinaryTree.cpp"
"src/Common.cpp"
"src/Sidewinder.cpp"
"src/Wilson.cpp"

#HPP
"include/pcg/engine/maze/AldousBroder.hpp"
"include/pcg/engine/maze/BinaryTree.hpp"
"include/pcg/engine/maze/Common.hpp"
"include/pcg/engine/maze/Sidewinder.hpp"
"include/pcg/engine/maze/Wilson.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC pcg-engine-math)
target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Utility)
