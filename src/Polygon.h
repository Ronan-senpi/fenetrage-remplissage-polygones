//
// Created by Aedrinios on 19/01/2021.
//
#ifndef PROJETMATH_POLYGON_H
#define PROJETMATH_POLYGON_H

#include <vector>
    #include "Math/Point.h"

static std::vector<Point> Vertices = {
        Point(0.5f,  0.5f),  // top right
        Point(0.5f, -0.5f),  // bottom right
        Point(-0.5f, -0.5f),  // bottom left
        Point(-0.5f,  0.5f)   // top left
};

static std::vector<uint16_t> Indices = {1,2,3,4};


#endif //PROJETMATH_POLYGON_H
