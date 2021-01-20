//
// Created by Ronan on 20/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_COLOR_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_COLOR_H

class Color {

#include <imgui.h>

private:
public:
	float r, g, b, a;

	Color() : r(1), g(1), b(1), a(1) {}

	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1) {}

	Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

	Color(ImVec4 v) : r(v.x), g(v.y), b(v.z), a(v.w) {}
};

#endif //FENETRAGE_REMPLISSAGE_POLYGONES_COLOR_H
