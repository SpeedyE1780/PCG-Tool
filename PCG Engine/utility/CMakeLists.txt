project(pcg-engine-utility)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/Enums.cpp"
"src/logging.cpp"

#HPP
"include/pcg/engine/utility/Concepts.hpp"
"include/pcg/engine/utility/Enums.hpp"
"include/pcg/engine/utility/logging.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

