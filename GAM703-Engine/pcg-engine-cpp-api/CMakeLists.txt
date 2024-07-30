project(pcg-engine-cpp-api)

find_library(pcg-engine-cpp-api-prebuilt pcg-engine-cpp-api ${PROJECT_SOURCE_DIR}/lib)
find_library(pcg-engine-math-prebuilt pcg-engine-math ${PROJECT_SOURCE_DIR}/lib)
find_library(pcg-engine-maze-generation-prebuilt pcg-engine-maze-generation ${PROJECT_SOURCE_DIR}/lib)
find_library(pcg-engine-combination-generation-prebuilt pcg-engine-combination-generation ${PROJECT_SOURCE_DIR}/lib)
find_library(pcg-engine-utility-prebuilt pcg-engine-utility ${PROJECT_SOURCE_DIR}/lib)
find_library(pcg-engine-level-generation-prebuilt pcg-engine-level-generation ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-combination-generation-prebuilt})
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-cpp-api-prebuilt})
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-level-generation-prebuilt})
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-math-prebuilt})
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-maze-generation-prebuilt})
target_link_libraries(${PROJECT_NAME} INTERFACE ${pcg-engine-utility-prebuilt})

add_custom_target(copy-pcg-engine-cpp-api-dll ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/dll
    ${COPY_DIRECTORY_PATH}/
    )

add_dependencies(${PROJECT_NAME} copy-pcg-engine-cpp-api-dll)
