//
// Created by Ronan on 16/01/2021.
//

#include "hodgman.h"
#include "../CustomMath.h" //cm::


std::vector<Point> hodgman::SutherlandHodgman(std::vector<Point> targetPolygon, std::vector<Point> clipPolygon) {
	// Set targetPolygon on outputlist
	// value to return
	std::vector<Point> outputList(targetPolygon);
	// For every Point of clip
	for (int edge = 0; edge < clipPolygon.size(); edge++) {
		// get first edge (Point1)
		Point edge_1_point = clipPolygon[edge];
		// Point 2
		// (edge+1)%clipPolygon.size() for get next one but if > size take first one
		Point edge_2_point = clipPolygon[(edge + 1) % clipPolygon.size()];

		std::vector<Point> inputList(outputList);
		outputList.clear();

		// For every edge of Inputlist(TargetPolygon)
		for (int i = 0; i < inputList.size(); i++) {
			// get first edge (Point1)
			Point current_point = inputList[i];
			// Point 2
			// (i+1)%inputList.size() for get prev one but if < size take last one
			Point prev_point = inputList[(i + inputList.size() - 1) % inputList.size()];

			// If Current point inside edge
			if (cm::inside(current_point, edge_1_point, edge_2_point)) {
				// and if prev point outside
				if (!cm::inside(prev_point, edge_1_point, edge_2_point)) {
					//add intersection point
					outputList.push_back(cm::intersection(edge_1_point, edge_2_point, prev_point, current_point));
				}
				//add current Point
				outputList.push_back(current_point);
				//else if prev point inside edge
			} else if (cm::inside(prev_point, edge_1_point, edge_2_point)) {
				//add intersection point
				outputList.push_back(cm::intersection(edge_1_point, edge_2_point, prev_point, current_point));
			}
		}
	}
	return outputList;
}
