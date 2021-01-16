//
// Created by Ronan on 16/01/2021.
//

#include "hodgman.h"


bool hodgman::inside(Point &point, Point &clip_edge_point1, Point &clip_edge_point2) {
	return false;
}

Point hodgman::intersection(Point &edge_point1, Point &edge_point2, Point &prev_point, Point &current_point) {
	return Point(0, 0);
}
std::vector<Point> hodgman::SutherlandHodgman(std::vector<Point> &targetPolygon, std::vector<Point> &clipPolygon) {

	std::vector<Point> outputList(targetPolygon);
	for(int edge =0; edge< clipPolygon.size();edge++){
		Point edge_1_point = clipPolygon[edge];
		Point edge_2_point = clipPolygon[(edge+1)%clipPolygon.size()];
		std::vector<Point> inputList(outputList);
		outputList.clear();

		for(int i =0; i<inputList.size();i++){
			Point current_point = inputList[i];
			Point prev_point = inputList[(i+inputList.size()-1)%inputList.size()];

			//Point intersecting_point = intersection()

			//intersection(Point cp1, Point cp2, Point s, Point e)
			if(inside(current_point,edge_1_point,edge_2_point)){
				if(!inside(prev_point,edge_1_point,edge_2_point)){
					outputList.push_back(intersection(edge_1_point, edge_2_point, prev_point, current_point));
				}
				outputList.push_back(current_point);
			}else if(inside(prev_point,edge_1_point, edge_2_point)){
				outputList.push_back(intersection(edge_1_point, edge_2_point, prev_point, current_point));
			}

		}
	}
	return outputList;
}
