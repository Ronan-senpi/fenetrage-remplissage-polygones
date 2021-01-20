//
// Created by Ronan on 16/01/2021.
//

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "ImguiSetup.h"
#include "iostream"
ImguiSetup::ImguiSetup() {}

void ImguiSetup::firstUpdate() {
	ImGui_ImplGlfwGL3_NewFrame();
}

void ImguiSetup::update() {
	mainWindow();
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

void ImguiSetup::mainWindow() {
	ImGui::Begin("Main");
	static float f = 0.0f;
	static int counter = 0;
	ImGui::Text("Filling :"); // Display some text (you can use a format string too)
	ImGui::ColorEdit3("fill color", (float*)&fillColor); // Edit 3 floats representing a color
	if (ImGui::Button("Fill polygon")) {
		std::cout << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << std::endl;
	}
	ImGui::Text("");
	ImGui::Text("Windowing :");
	ImGui::Checkbox("Window tracing", &isWindowTracing);      // Edit bools storing our windows open/close state
	if (ImGui::Button("Cut"))
	{
		counter++; //cut
	}

	ImGui::Text("Application average %.3f ms/frame \n (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

Color ImguiSetup::getFillColor() {
	return Color(fillColor);
}

ImguiSetup::~ImguiSetup() {
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}
