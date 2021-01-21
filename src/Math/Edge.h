//
// Created by Ronan on 21/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_EDGE_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_EDGE_H

#include "Point.h"
class Edge {
public:
	Edge();
	Point A,B;
	Edge(Point a, Point b): A(a), B(b){}
};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_EDGE_H
