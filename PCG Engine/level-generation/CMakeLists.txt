project(PCG-Engine-Level-Generation)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/MultiDimensionalGeneration.cpp"
"src/Node.cpp"
"src/SimpleGeneration.cpp"
"src/WaveFunctionCollapse.cpp"

#HPP
"include/pcg/engine/level-generation/GenerationData.hpp"
"include/pcg/engine/level-generation/MultiDimensionalGeneration.hpp"
"include/pcg/engine/level-generation/Node.hpp"
"include/pcg/engine/level-generation/SimpleGeneration.hpp"
"include/pcg/engine/level-generation/WaveFunctionCollapse.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Math)
target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Utility)

