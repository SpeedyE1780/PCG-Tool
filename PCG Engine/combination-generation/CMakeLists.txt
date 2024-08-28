project(pcg-engine-combination-generation)

enable_testing()

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/CombinationGenerator.cpp"
"src/SequenceGenerator.cpp"

#HPP
"include/pcg/engine/combination-generation/CombinationGenerator.hpp"
"include/pcg/engine/combination-generation/SequenceGenerator.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE pcg-engine-math)

add_subdirectory(tests)
