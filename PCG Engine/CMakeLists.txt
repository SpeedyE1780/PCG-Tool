cmake_minimum_required(VERSION 3.27)

project(PCG-Engine)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_GENERATOR} STREQUAL "Ninja")
set(COPY_DIRECTORY_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
set(COPY_DIRECTORY_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>)
endif()

add_subdirectory(3rd-party/game-engine)

add_subdirectory(c-api)
add_subdirectory(combination-generation)
add_subdirectory(cpp-api)
add_subdirectory(demos/console)
add_subdirectory(demos/gam703-engine)
add_subdirectory(level-generation)
add_subdirectory(math)
add_subdirectory(maze)
add_subdirectory(utility)

find_package(Doxygen)
if (Doxygen_FOUND)
    add_subdirectory(docs)
    add_dependencies(pcg-engine-c-api pcg-engine-docs)
    add_dependencies(pcg-engine-cpp-api pcg-engine-docs)
else()
	message(STATUS "Doxygen not found, no docs will be built")
endif()
