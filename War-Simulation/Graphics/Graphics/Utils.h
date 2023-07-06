#pragma once
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <typeinfo>
#include <vector>
#include <queue>
#include <iostream>
#include "Definitions.h"

class Utils {
public:
	static double EuclideanDistance(int x, int y, int xx, int yy);
	static double ManhattanDistance(int x, int y, int xx, int yy);
	static std::pair<int, int> generateRandomCoordinates(int start_x, int end_x, int start_y, int end_y, int* maze[MSZ]);
	static std::pair< std::pair<int, int>, std::pair<int, int> > generateRandomBlockCoordinates(int start_x, int end_x, int start_y, int end_y, int blocksize);
	static double getAlpha(double x1, double y1, double x2, double y2) {
		double dx = x2 - x1;
		double dy = y2 - y1;
		double mag1 = sqrt(dx * dx + dy * dy);
		double mag2 = 1.0;
		double dot = dx * mag2;
		double alpha = acos(dot / (mag1 * mag2));
		if (dy < 0) {
			alpha = -alpha;
		}
		return alpha;
	}

};

