//
// Created by Ronan on 16/01/2021.
//

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "ImguiSetup.h"
ImguiSetup::ImguiSetup(GLFWwindow *window) {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

void ImguiSetup::firstUpdate() {
	ImGui_ImplGlfwGL3_NewFrame();
}

void ImguiSetup::update() {
	static float f = 0.0f;
	static int counter = 0;
	ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
	ImGui::Checkbox("Another Window", &show_another_window);

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}

void ImguiSetup::lastUpdate() {
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

}
