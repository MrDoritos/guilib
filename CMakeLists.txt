cmake_minimum_required(VERSION 3.10)

set(GUILIB_NAME guilib)

project(${GUILIB_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GUILIB_FILES shaders assets)
set(GUILIB_SOURCE_DIR src/guilib)
set(GUILIB_INCLUDE_DIR src/guilib)
set(GUILIB_WIDGETS_LIBRARY widgets)
set(GUILIB_RESOURCES_LIBRARY resources)

set(THIRDPARTY_INCLUDE_DIR thirdparty)

add_subdirectory(${THIRDPARTY_INCLUDE_DIR}/tinyobjloader)

add_library(${GUILIB_WIDGETS_LIBRARY}
    ${GUILIB_SOURCE_DIR}/ui_element.cpp
    ${GUILIB_SOURCE_DIR}/ui_text.cpp
    ${GUILIB_SOURCE_DIR}/ui_slider.cpp
    ${GUILIB_SOURCE_DIR}/ui_toggle.cpp
)

add_library(${GUILIB_RESOURCES_LIBRARY}
    ${GUILIB_SOURCE_DIR}/text.cpp
    ${GUILIB_SOURCE_DIR}/camera.cpp
    ${GUILIB_SOURCE_DIR}/texture.cpp
    ${GUILIB_SOURCE_DIR}/shader.cpp
    ${GUILIB_SOURCE_DIR}/shader_program.cpp
    ${GUILIB_SOURCE_DIR}/mesh.cpp
)

add_executable(${GUILIB_NAME}
    ${GUILIB_SOURCE_DIR}/common.cpp
)

find_path(GL_INCLUDE_DIR GL/gl.h)
find_path(GLES3_INCLUDE_DIR GLES3/gl3.h)
find_path(EGL_INCLUDE_DIR EGL/egl.h)
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
find_path(GLM_INCLUDE_DIR glm/glm.hpp)
find_path(tinyobjloader_INCLUDE_DIR tiny_obj_loader.h)

find_library(GL_LIBRARY GL)
find_library(GLFW_LIBRARY glfw)
find_library(tinyobjloader_LIBRARY tinyobjloader)

target_include_directories(${GUILIB_RESOURCES_LIBRARY} PUBLIC 
    ${GUILIB_INCLUDE_DIR}
    ${GL_INCLUDE_DIR}
    ${GLES3_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${THIRDPARTY_INCLUDE_DIR}
)

target_link_libraries(${GUILIB_RESOURCES_LIBRARY}
    ${GL_LIBRARY}
    ${GLFW_LIBRARY}
    ${tinyobjloader_LIBRARY}
)

target_link_libraries(${GUILIB_WIDGETS_LIBRARY}
    ${GUILIB_RESOURCES_LIBRARY}
)

target_link_libraries(${GUILIB_NAME}
    ${GUILIB_WIDGETS_LIBRARY}
    ${GUILIB_RESOURCES_LIBRARY}
)

target_compile_options(${GUILIB_NAME} PUBLIC
    -g #-O2
)

target_compile_options(${GUILIB_RESOURCES_LIBRARY} PUBLIC
    -g #-O2
)

target_compile_options(${GUILIB_WIDGETS_LIBRARY} PUBLIC
    -g #-O2
)

file(COPY ${GUILIB_FILES} DESTINATION ${CMAKE_BINARY_DIR})