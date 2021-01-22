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
        apply_lca();
	}
	//End : Filling
	ImGui::Text("");
	//Start : Windowing
	ImGui::Text("Windowing :");
	ImGui::Checkbox("Window tracing", &isWindowTracing);
	// Begin : Clipping
	if (ImGui::Button("Cut"))
	{
		//Call SutherlandHodgman
		std::vector<Point> b = hodgman::SutherlandHodgman(*_polygonVertices, *_cutVertices);
		//If SutherlandHodgman's result empty, second call for try on other "direction"
		if (b.size() == 0){
			// Inverse polygon and cut array
			std::reverse(_polygonVertices->begin(),_polygonVertices->end());
			std::reverse(_cutVertices->begin(),_cutVertices->end());
			b = hodgman::SutherlandHodgman(*_polygonVertices, *_cutVertices);
		}
		//Remove old polygon & cut
		clear();
		//Add new one
		_polygonVertices->insert(_polygonVertices->end(), b.begin(), b.end());
		for (int i = 0; i < _polygonVertices->size(); ++i) {
			_polygonIndices->push_back(i);
		}
	}
	//End : Clipping
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
    isFilling=false;
}

bool ImguiSetup::getIsFilling() {
    return isFilling;
}
void ImguiSetup::delimit(){
    std::vector<Point> cutVertices = *_cutVertices;
    polygon_xmin=cutVertices[0].X;
    polygon_xmax=cutVertices[0].X;
    polygon_ymin=cutVertices[0].Y;
    polygon_ymax=cutVertices[0].Y;
    for (int i=0; i<cutVertices.size(); i++)
    {
        if(polygon_xmin>cutVertices[i].X)
            polygon_xmin=cutVertices[i].X;
        if(polygon_xmax<cutVertices[i].X)
            polygon_xmax=cutVertices[i].X;
        if(polygon_ymin>cutVertices[i].Y)
            polygon_ymin=cutVertices[i].Y;
        if(polygon_ymax<cutVertices[i].Y)
            polygon_ymax=cutVertices[i].Y;
    }
}

void ImguiSetup::fill_inter(float ligne){
    std::vector<Point> cutVertices = *_cutVertices;
    std::vector<unsigned int> cutIndices = *_cutIndices;
    int x1,x2,y1,y2;
    int x_cote;
    int indice_inter=0;
    for(int i=0;i<cutVertices.size();i++)
    {
        if(cutVertices[i].Y<cutVertices[i+1].Y){
            x1=cutVertices[i].X;
            y1=cutVertices[i].Y;
            x2=cutVertices[i+1].X;
            y2=cutVertices[i+1].Y;
        }
        else{
            x2=cutVertices[i].X;
            y2=cutVertices[i].Y;
            x1=cutVertices[i+1].X;
            y1=cutVertices[i+1].Y;
        }
        if(ligne<=y2 && ligne >=y1){
            if((y1-y2)==0) //To avoid the division by zero
                x_cote=x1;
            else
            {
                x_cote=((x2-x1)*(ligne-y1))/(y2-y1);
                x_cote+=x1;
            }
            if(x_cote<=polygon_xmax && x_cote>=polygon_xmin)
                LCA_inter[indice_inter]=x_cote;
                indice_inter++;
        }

    }
}

void ImguiSetup::draw_line(float ligne){
    //We should sort LCA_inter but i'm not sure
    
    for(int i=0; i<LCA_inter.size(); i+=2)
    {
        // We draw here the line with the coordinates (LCA_inter[i],ligne,LCA_inter[i+1],ligne);
    }
}

void ImguiSetup::apply_lca() {
    float ligne;
    std::vector<Point> cutVertices = *_cutVertices;
    std::vector<unsigned int> cutIndices = *_cutIndices;
    if(cutVertices.size()>3){
        isFilling = true;
        delimit();
        ligne = polygon_ymin+0.01;
        while(ligne<=polygon_ymax){
            fill_inter(ligne);
            draw_line(ligne);
            ligne=ligne+0.01;
        }
    }
}