cmake_minimum_required(VERSION 3.17)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

cmake_policy(SET CMP0091 NEW)

project(ProjetMath)

add_executable(ProjetMath vendor/glad/src/glad.c vendor/imgui-1.60/src/imgui.cpp vendor/imgui-1.60/src/imgui_draw.cpp vendor/imgui-1.60/src/imgui_demo.cpp vendor/imgui-1.60/src/imgui_impl_glfw_gl3.cpp src/main.cpp)

set_property(TARGET ProjetMath PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_compile_features(ProjetMath PRIVATE cxx_std_20)
target_compile_options(ProjetMath PRIVATE "$<$<CONFIG:Release>:-O2>")

find_path(STB_INCLUDE_DIRS "stb.h")
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

target_include_directories(ProjetMath PRIVATE
		"vendor/glad/include"
		"vendor/imgui-1.60/include"
		${STB_INCLUDE_DIRS})

target_link_libraries(ProjetMath PRIVATE
		glfw
		glm)

add_custom_command(TARGET ProjetMath PRE_BUILD
		COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")