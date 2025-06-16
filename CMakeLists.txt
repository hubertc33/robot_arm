cmake_minimum_required(VERSION 3.10)
project(robot_arm)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

# GLAD
include_directories(lib/glad/include)
add_library(glad STATIC lib/glad/src/glad.c)

# GLM
include_directories(lib/glm)

# ImGui
include_directories(lib/imgui lib/imgui/backends)
file(GLOB IMGUI_SRC
    lib/imgui/*.cpp
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SRC})

# Źródła naszego projektu
file(GLOB SOURCES src/*.cpp)
file(GLOB SOURCES src/*.cpp)
add_executable(robot ${SOURCES})

# Linkowanie bibliotek
target_link_libraries(robot glad glfw imgui opengl32)

# Kopiowanie shaderów tylko gdy zmienione (ręcznie śledzone przez Make)
add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders
    COMMENT "Kopiowanie shaderów do katalogu binarnego"
)

# Ustaw, że robot zależy od skopiowanych shaderów
add_dependencies(robot copy_shaders)