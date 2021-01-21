//
// Created by Ronan on 16/01/2021.
//

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "ImguiSetup.h"
#include "iostream"
#include "Math/Windowing/hodgman.h"

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
void ImguiSetup::init(GLFWwindow *window, std::vector<Point> *polygonVertices, std::vector<Point> *cutVertices, std::vector<unsigned int> *polygonIndices, std::vector<unsigned int> *cutIndices) {
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
    _polygonVertices = polygonVertices;
    _cutVertices = cutVertices;
    _polygonIndices = polygonIndices;
    _cutIndices = cutIndices;
}

bool ImguiSetup::getIsWindowTracing() {
	return isWindowTracing;
}

void ImguiSetup::mainWindow() {
	//Set name of windows
	ImGui::Begin("Main");
	//Begin : Filling
	ImGui::Text("Right-click to place points");
	ImGui::Text("(The polygon appears after 4 clicks)");
	ImGui::Text("(convex polygon only)");
	ImGui::Text("");
	ImGui::Text("Filling :"); // Display some text (you can use a format string too)
	ImGui::ColorEdit3("fill color", (float*)&fillColor); // Edit 3 floats representing a color
	if (ImGui::Button("Fill polygon")) {
		std::cout << getFillColor().r << " " << getFillColor().g << " " << getFillColor().b << std::endl;
	}
	//End : Filling
	ImGui::Text("");
	//Start : Windowing
	ImGui::Text("Windowing :");
	ImGui::Checkbox("Window tracing", &isWindowTracing);
	if (ImGui::Button("Cut"))
	{

		std::vector<Point> b = hodgman::SutherlandHodgman(*_polygonVertices, *_cutVertices);
		if (b.size() == 0){
			std::reverse(_polygonVertices->begin(),_polygonVertices->end());
			std::reverse(_cutVertices->begin(),_cutVertices->end());
			b = hodgman::SutherlandHodgman(*_polygonVertices, *_cutVertices);
		}
		//clear();
		clear();
		_polygonVertices->insert(_polygonVertices->end(), b.begin(), b.end());
		for (int i = 0; i < _polygonVertices->size(); ++i) {
			_polygonIndices->push_back(i);
		}
	}
	//End : Windowing
	ImGui::Text("");
	if (ImGui::Button("Clear")) {
		std::cout << "Clear" << std::endl;
		clear();
	}

	ImGui::Text("");
	//stats
	ImGui::Text("Application average %.3f ms/frame \n (%.1f FPS)",
			 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//end
	ImGui::End();
}

Color ImguiSetup::getFillColor() {
	return Color(fillColor);
}

ImguiSetup::~ImguiSetup() {
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

void ImguiSetup::clear() {
    _polygonVertices->clear();
    _polygonIndices->clear();
    _cutVertices->clear();
    _cutIndices->clear();
}