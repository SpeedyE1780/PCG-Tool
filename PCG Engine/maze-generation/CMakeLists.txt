project(pcg-engine-maze-generation)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/AldousBroder.cpp"
"src/BinaryTree.cpp"
"src/BlobbyDivision.cpp"
"src/Common.cpp"
"src/Eller.cpp"
"src/GrowingTree.cpp"
"src/HuntAndKill.cpp"
"src/Kruskal.cpp"
"src/Prim.cpp"
"src/RecursiveBacktracker.cpp"
"src/RecursiveDivision.cpp"
"src/Sidewinder.cpp"
"src/Utility.cpp"
"src/Wilson.cpp"

#HPP
"include/pcg/engine/maze-generation/AldousBroder.hpp"
"include/pcg/engine/maze-generation/BinaryTree.hpp"
"include/pcg/engine/maze-generation/BlobbyDivision.hpp"
"include/pcg/engine/maze-generation/Common.hpp"
"include/pcg/engine/maze-generation/Eller.hpp"
"include/pcg/engine/maze-generation/GrowingTree.hpp"
"include/pcg/engine/maze-generation/HuntAndKill.hpp"
"include/pcg/engine/maze-generation/Kruskal.hpp"
"include/pcg/engine/maze-generation/Prim.hpp"
"include/pcg/engine/maze-generation/RecursiveBacktracker.hpp"
"include/pcg/engine/maze-generation/RecursiveDivision.hpp"
"include/pcg/engine/maze-generation/Sidewinder.hpp"
"include/pcg/engine/maze-generation/Wilson.hpp"

#INTERNAL HPP
"include-internal/pcg/engine/maze-generation/Utility.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include-internal/)

target_link_libraries(${PROJECT_NAME} PUBLIC pcg-engine-math)
target_link_libraries(${PROJECT_NAME} PUBLIC pcg-engine-utility)
