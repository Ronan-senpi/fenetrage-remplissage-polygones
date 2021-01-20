//
// Created by Ronan on 16/01/2021.
//

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "ImguiSetup.h"
ImguiSetup::ImguiSetup() {}

void ImguiSetup::firstUpdate() {
	ImGui_ImplGlfwGL3_NewFrame();
}

void ImguiSetup::update() {
	static float f = 0.0f;
	static int counter = 0;
	ImGui::Text("Remplissage :"); // Display some text (you can use a format string too)
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
	if (ImGui::Button("Remplir")) {// Buttons return true when clicked (NB: most widgets return true when edited/activated)
		counter++;
		ClickedFillLabel = "Cliquez dans le polygone a remlplir";
	}
	ImGui::Text(ClickedFillLabel.c_str());

	ImGui::Text("");
	ImGui::Text("Fenêtrage :");
	ImGui::Checkbox("Traçage de fenêtre", &isWindowTracing);      // Edit bools storing our windows open/close state
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

void ImguiSetup::init(GLFWwindow *window) {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

bool ImguiSetup::getIsWindowTracing() {
	return isWindowTracing;
}
