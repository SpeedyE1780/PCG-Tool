cmake_minimum_required(VERSION 3.27)

project(PCG-Engine)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
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

add_subdirectory(core)
add_subdirectory(demos/console)
add_subdirectory(math)
add_subdirectory(utility)
