//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H

#include "vector"
#include "Point.h"

class hodgman {
	static std::vector<Point> SutherlandHodgman(std::vector<Point>& subjectPolygon, std::vector<Point>& clipPolygon);
	static Point intersection(Point& edge_point1, Point& edge_point2, Point& prev_point, Point& current_point);
	static bool inside(Point& point, Point& clip_edge_point1, Point& clip_edge_point2);
};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_HODGMAN_H
