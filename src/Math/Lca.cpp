//
// Created by Ronan on 17/01/2021.
//

#include "Lca.h"
void Lca::delimit(vector<Point> listVertices){
    _xmin=listVertices[0].X;
    _xmax=listVertices[0].X;
    _ymin=listVertices[0].Y;
    _ymax=listVertices[0].Y;
    for (int i=0; i<listVertices.size(); i++)
    {
        if(_xmin>listVertices[i].X)
            _xmin=listVertices[i].X;
        if(_xmax<listVertices[i].X)
            _xmax=listVertices[i].X;
        if(_ymin>listVertices[i].Y)
            _ymin=listVertices[i].Y;
        if(_ymax<listVertices[i].Y)
            _ymax=listVertices[i].Y;
    }
    //cout << "x : " << _xmin << " " << _xmax << " y : " << _ymin << " " << _ymax << endl;
}

void Lca::draw(){

}