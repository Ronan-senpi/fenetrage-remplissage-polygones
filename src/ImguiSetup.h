//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Color.h"
#include "vector"
#include "Math/Point.h"
#include "Math/Lca.h"

class ImguiSetup {
public:
	ImguiSetup();
	~ImguiSetup();
	void init(GLFWwindow *window);
    void init(GLFWwindow *window,
			  std::vector<Point> *polygonVertices,
			  std::vector<Point> *cutVertices,
			  std::vector<unsigned int> *polygonIndices,
			  std::vector<unsigned int> *cutIndices);
    void firstUpdate();
	void update();
	void lastUpdate();
	bool getIsWindowTracing();
	Color getFillColor();
    void clear();
    bool getIsFilling();
    void delimit();
    void fill_inter(float ligne);
    void draw_line(float ligne);
    void apply_lca();


private:
	void mainWindow();
	ImVec4 fillColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool isWindowTracing = false;
    bool isFilling = false;
    std::vector<Point> *_polygonVertices;
    std::vector<Point> *_cutVertices;
    std::vector<unsigned int> *_polygonIndices;
    std::vector<unsigned int> *_cutIndices;
    std::vector<float> LCA_inter;
    float polygon_xmin,polygon_xmax,polygon_ymin,polygon_ymax;

};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_IMGUISETUP_H
