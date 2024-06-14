project(PCG-Engine-CPP-API)

add_library(${PROJECT_NAME} SHARED)

target_compile_definitions(${PROJECT_NAME} PRIVATE PCG_ENGINE_CPP_API_EXPORT)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/api.cpp"

#HPP
"include/pcg/engine/cpp-api/api.hpp"
"include/pcg/engine/cpp-api/config.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC PCG-Engine-Core)
