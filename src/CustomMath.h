//
// Created by Ronan on 17/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_CUSTOMMATH_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_CUSTOMMATH_H


#include "Point.h"
namespace  cm {
		static Point intersection(Point &edge_point1, Point &edge_point2, Point &prev_point, Point &current_point);
		static bool inside(Point &point, Point &clip_edge_point1, Point &clip_edge_point2);
}

#endif //FENETRAGE_REMPLISSAGE_POLYGONES_CUSTOMMATH_H
