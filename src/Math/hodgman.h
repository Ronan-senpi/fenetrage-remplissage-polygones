//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H

#include "vector"
#include "Point.h"

class hodgman {
	static std::vector<Point> SutherlandHodgman(std::vector<Point> &subjectPolygon, std::vector<Point> &clipPolygon);
};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H
