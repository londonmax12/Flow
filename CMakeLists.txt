cmake_minimum_required(VERSION "3.24.0")

project("Flow")

set(CMAKE_CXX_STANDARD 17)

add_executable("Example"
    "Example/src/main.cpp"
)

target_include_directories("Example" PRIVATE ${PROJECT_NAME}/include)

add_library("${PROJECT_NAME}"
    "${PROJECT_NAME}/src/flow.cpp"
    "${PROJECT_NAME}/include/flow.h"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)

target_link_libraries("Example" ${PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "Example")