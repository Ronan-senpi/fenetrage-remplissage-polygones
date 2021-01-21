//
// Created by Ronan on 16/01/2021.
//

#include "hodgman.h"
#include "../CustomMath.h" //cm::


std::vector<Point> hodgman::SutherlandHodgman(std::vector<Point> targetPolygon, std::vector<Point> clipPolygon) {
	std::vector<Point> outputList(targetPolygon);
	for(int edge =0; edge< clipPolygon.size();edge++){
		Point edge_1_point = clipPolygon[edge];
		Point edge_2_point = clipPolygon[(edge+1)%clipPolygon.size()];
		std::vector<Point> inputList(outputList);
		outputList.clear();

		for(int i =0; i<inputList.size();i++){
			Point current_point = inputList[i];
			Point prev_point = inputList[(i+inputList.size()-1)%inputList.size()];

			//Point2d intersecting_point = intersection()

			//intersection(Point2d cp1, Point2d cp2, Point2d s, Point2d e)
			if(cm::inside(current_point,edge_1_point,edge_2_point)){
				if(!cm::inside(prev_point,edge_1_point,edge_2_point)){
					outputList.push_back(cm::intersection(edge_1_point, edge_2_point, prev_point, current_point));
				}
				outputList.push_back(current_point);
			}else if(cm::inside(prev_point,edge_1_point, edge_2_point)){
				outputList.push_back(cm::intersection(edge_1_point, edge_2_point, prev_point, current_point));
			}

		}
	}
	return outputList;
}
