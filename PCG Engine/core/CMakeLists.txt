project(PCG-Engine-Core)

enable_testing()

add_library(${PROJECT_NAME} SHARED)

target_compile_definitions(${PROJECT_NAME} PRIVATE PCG_ENGINE_CORE_EXPORT)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/api.cpp"
"src/Maze.cpp"
"src/MultiDimensionalGeneration.cpp"
"src/node.cpp"
"src/SimpleGeneration.cpp"
"src/WaveFunctionCollapse.cpp"

#HPP
"include/pcg/engine/core/api.hpp"
"include/pcg/engine/core/config.hpp"
"include/pcg/engine/core/GenerationData.hpp"
"include/pcg/engine/core/Maze.hpp"
"include/pcg/engine/core/MultiDimensionalGeneration.hpp"
"include/pcg/engine/core/node.hpp"
"include/pcg/engine/core/SimpleGeneration.hpp"
"include/pcg/engine/core/WaveFunctionCollapse.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Math)
target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Utility)

