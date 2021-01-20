//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H

#include <GLFW/glfw3.h>
#include <string>

class ImguiSetup {
public:
	ImguiSetup();
	void init(GLFWwindow *window);
	void firstUpdate();
	void update();
	void lastUpdate();
	bool getIsWindowTracing();

private:
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	std::string ClickedFillLabel;
	bool isWindowTracing = false;

};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
