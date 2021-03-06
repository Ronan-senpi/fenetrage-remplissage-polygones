cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_STANDARD 20)

project(fenetrage-remplissage-polygones)

add_executable(fenetrage-remplissage-polygones vendor/glad/src/glad.c src/main.cpp src/Shader.cpp src/Shader.h src/helpers/FileHelper.h src/helpers/FileHelper.cpp src/Polygon.h src/Mesh.cpp src/Mesh.h src/Application.cpp src/Application.h src/Camera.cpp src/Camera.h vendor/imgui-1.60/imconfig.h vendor/imgui-1.60/imgui.cpp vendor/imgui-1.60/imgui.h vendor/imgui-1.60/imgui_demo.cpp vendor/imgui-1.60/imgui_draw.cpp vendor/imgui-1.60/imgui_impl_glfw_gl3.cpp vendor/imgui-1.60/imgui_impl_glfw_gl3.h vendor/imgui-1.60/imgui_internal.h vendor/imgui-1.60/stb_rect_pack.h vendor/imgui-1.60/stb_textedit.h vendor/imgui-1.60/stb_truetype.h src/ImguiSetup.cpp src/ImguiSetup.h src/Math/Windowing/hodgman.cpp src/Math/Windowing/hodgman.h src/Math/Point.cpp src/Math/Point.h src/Math/Lca.cpp src/Math/Lca.h src/Math/CustomMath.cpp src/Math/CustomMath.h src/Color.h)


target_include_directories(fenetrage-remplissage-polygones PRIVATE
        "vendor/glad/include"
		"vendor/glfw-3.3.2/include"
		"vendor/glm-0.9.9.8"
		"vendor/imgui-1.60")

target_link_directories(fenetrage-remplissage-polygones PRIVATE
		"vendor/glfw-3.3.2/lib")

target_link_libraries(fenetrage-remplissage-polygones PRIVATE
		glfw3)

add_custom_command(TARGET fenetrage-remplissage-polygones PRE_BUILD
		COMMAND robocopy ${PROJECT_SOURCE_DIR}/resources/ ${PROJECT_BINARY_DIR}/resources /E /NS /NC /NFL /NDL /NP /NJH /NJS  || cmd /c "exit /b 0")