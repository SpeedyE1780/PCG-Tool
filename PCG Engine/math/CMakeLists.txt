project(PCG-Engine-Math)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/random.cpp"
"src/vector3.cpp"

#HPP
"include/pcg/engine/math/enums.hpp"
"include/pcg/engine/math/random.hpp"
"include/pcg/engine/math/vector3.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE PCG-Engine-Utility)
