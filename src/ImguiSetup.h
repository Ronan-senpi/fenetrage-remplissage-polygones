//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Color.h"
class ImguiSetup {
public:
	ImguiSetup();
	~ImguiSetup();
	void init(GLFWwindow *window);
	void firstUpdate();
	void update();
	void lastUpdate();
	bool getIsWindowTracing();
	Color getFillColor();


private:
	void mainWindow();
	ImVec4 fillColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool isWindowTracing = false;

};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
