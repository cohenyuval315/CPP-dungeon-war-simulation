
#pragma once
#include "Cell.h"
#include <math.h>

class DistanceCompareCells
{
private:
	int target_x;
	int target_y;
	
public:
	DistanceCompareCells();
	DistanceCompareCells(int x, int y);
	~DistanceCompareCells();

	void setTarget(int x, int y) { target_x = x; target_y = y; }

	bool operator() (Cell* c1, Cell* c2) {
		return _distance(c1) > _distance(c2);
	}

	double _distance(Cell* c) {
		int x_distance = target_x - c->getRow();
		int y_distance = target_y - c->getColumn();
		double d = x_distance * x_distance + y_distance * y_distance;
		return sqrt(d);
	}

};


