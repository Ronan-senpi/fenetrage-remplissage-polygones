//
// Created by Ronan on 16/01/2021.
//

#ifndef FENETRAGE_REMPLISSAGE_POLYGONES_POINT_H
#define FENETRAGE_REMPLISSAGE_POLYGONES_POINT_H


class Point {
public:
	Point();
	inline Point(float x, float y) {
		X = x;
		Y = y;
	}

	float X;
	float Y;
};


#endif //FENETRAGE_REMPLISSAGE_POLYGONES_POINT_H
