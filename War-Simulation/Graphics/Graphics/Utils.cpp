#include "Utils.h"


std::pair< std::pair<int, int>, std::pair<int, int> > Utils::generateRandomBlockCoordinates(int start_x, int end_x, int start_y, int end_y, int blocksize)
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
	if (end_x - start_x < blocksize || end_y - start_y < blocksize) {
		exit(1);
	}
	/*
	do
	{
		
		isOk = true;
		int x_start = start_x + static_cast<int>(rand()) / RAND_MAX * (end_x - start_x);
		int y_start = start_y + static_cast<int>(rand()) / RAND_MAX * (end_y - start_y);
		for (int i = 0; i < blocksize; i++) {
			for (int j = 0; j < blocksize; j++) {
				if (maze[i][j] != SPACE) {
					isOk = false;
					break;
				}
			}
		}

	} while (isOk == false);*/
	return std::make_pair(std::make_pair(x_start, y_start), std::make_pair(x_end, y_end));
}

std::pair<int, int> Utils::generateRandomCoordinates(int start_x, int end_x, int start_y, int end_y, int* maze[MSZ])
{
	int x, y;
	do
	{
		x = start_x + static_cast<double>(rand()) / RAND_MAX * (end_x - start_x);
		y = start_y + static_cast<double>(rand()) / RAND_MAX * (end_y - start_y);
	} while (maze[x][y] != SPACE);
	return std::make_pair(x, y);
}

double Utils::EuclideanDistance(int x, int y, int xx, int yy) {
	double distance = sqrt(abs(xx - x) * abs(xx - x) + abs(yy - y) * abs(yy - y));
	return distance;
}

double Utils::ManhattanDistance(int x, int y, int xx, int yy) {
	double distance = abs(xx - x) + abs(yy - y);
	return distance;
}