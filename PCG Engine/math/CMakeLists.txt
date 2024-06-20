project(pcg-engine-math)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/Random.cpp"
"src/Vector3.cpp"

#HPP
"include/pcg/engine/math/Enums.hpp"
"include/pcg/engine/math/Random.hpp"
"include/pcg/engine/math/Vector3.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE pcg-engine-utility)
