//
// Created by Ronan on 17/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_LCA_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_LCA_H


#include "Point.h"
#include "vector"
#include "iostream"
using namespace std;

class Lca {
private:
    float _xmin,_xmax,_ymin,_ymax;
    std::vector<Point> intersects;
public:
    void delimit(vector<Point> listVertices);
    void draw();
};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_LCA_H
