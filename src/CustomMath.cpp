//
// Created by Ronan on 17/01/2021.
//

#include "CustomMath.h"


Point cm::intersection(Point &edge_point1, Point &edge_point2, Point &prev_point, Point &current_point) {
	Point dc = {edge_point1.X - edge_point2.X, edge_point1.Y - edge_point2.Y};
	Point dp = {prev_point.X - current_point.X, prev_point.Y - current_point.Y};

	float n1 = edge_point1.X * edge_point2.Y - edge_point1.Y * edge_point2.X;
	float n2 = prev_point.X * current_point.Y - prev_point.Y * current_point.X;
	float n3 = 1.0f / (dc.X * dp.Y - dc.Y * dp.X);

	return {(n1 * dp.X - n2 * dc.X) * n3, (n1 * dp.Y - n2 * dc.Y) * n3};
}

bool cm::inside(Point &point, Point &clip_edge_point1, Point &clip_edge_point2) {
	return (clip_edge_point2.Y - clip_edge_point1.Y) * point.X + (clip_edge_point1.X - clip_edge_point2.X) * point.Y
	       + (clip_edge_point2.X * clip_edge_point1.Y - clip_edge_point1.X * clip_edge_point2.Y) < 0;
}
