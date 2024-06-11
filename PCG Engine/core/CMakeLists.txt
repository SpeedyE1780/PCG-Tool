project(PCG-Engine-Core)

enable_testing()

add_library(${PROJECT_NAME} SHARED)

target_compile_definitions(${PROJECT_NAME} PRIVATE PCG_ENGINE_CORE_EXPORT)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/generators.cpp"
"src/node.cpp"

#HPP
"include/pcg/engine/core/api.hpp"
"include/pcg/engine/core/config.hpp"
"include/pcg/engine/core/generators.hpp"
"include/pcg/engine/core/node.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Math)
target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Utility)

