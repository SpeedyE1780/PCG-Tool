project(pcg-engine-tests)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
#CPP
"src/PCGTest.cpp"

#HPP
"include/pcg/engine/tests/PCGTest.hpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PUBLIC pcg-engine-math)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest)
