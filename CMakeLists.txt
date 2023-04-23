cmake_minimum_required(VERSION "3.24.0")

project("Flow")

set(CMAKE_CXX_STANDARD 17)

add_executable("Example-OpenGL" WIN32
    "Example-OpenGL/src/main.cpp"
    "Example-OpenGL/middleware/glad/include/glad/glad.h"
    "Example-OpenGl/middleware/glad/src/glad.c"
    "${PROJECT_NAME}/include/flow/impl/flow_opengl_impl.h"
    "${PROJECT_NAME}/src/impl/flow_opengl_impl.cpp"			
)

target_include_directories("Example-OpenGL" PRIVATE ${PROJECT_NAME}/include)
target_include_directories("Example-OpenGL" PRIVATE "Example-OpenGL/middleware/glad/include")

add_library("${PROJECT_NAME}"
    "${PROJECT_NAME}/include/flow/flow.h"
    "${PROJECT_NAME}/include/flow/flow_types.h"
    "${PROJECT_NAME}/include/flow/flow_renderer.h" 
    "${PROJECT_NAME}/include/flow/flow_widgets.h"
    "${PROJECT_NAME}/src/flow.cpp"
    "${PROJECT_NAME}/src/flow_renderer.cpp"
    "${PROJECT_NAME}/src/flow_widgets.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}/include)

target_link_libraries("Example-OpenGL" ${PROJECT_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "Example-OpenGL")