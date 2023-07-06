#include "HasVision.h"

HasVision::HasVision()
{
}

HasVision::HasVision(int visionX, int visionY) {
	setVisionX(visionX);
	setVisionY(visionY);
}

HasVision::HasVision(int visionN) {
	setVisionN(visionN);

}

HasVision::~HasVision() {

}


bool HasVision::hasWallBetween(int x1, int y1, int x2, int y2, int* maze[MSZ]) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;
	int x = x1;
	int y = y1;
	while (x != x2 || y != y2) {
		if (maze[x][y] == WALL) {
			return true;
		}
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x += sx;
		}
		if (e2 < dx) {
			err += dx;
			y += sy;
		}
	}
	return false;
}

bool HasVision::CheckSurrounding(int row, int col, int* maze[MSZ], int myId, std::vector<int> teamIds) {
	targets.clear();
	bool isTeam;
	setNumVisibleEnemy(0);
	setNumVisibleTeam(1);
	int vx = getVisionX();
	int vy = getVisionY();
	int i, j;
	std::vector<Node*> cells;
	std::vector<int>::iterator it;
	int x_start = row - vx;
	int y_start = col - vy;
	int x_end = row + vx;
	int y_end = col + vy;

	if (x_end > MSZ) { x_end = MSZ; }
	if (y_end > MSZ) { y_end = MSZ; }
	if (x_start < 0) { x_start = 0; }
	if (y_start < 0) { y_start = 0; }

	for (i = x_start; i < x_end; i++) {
		for (j = y_start; j < y_end; j++) {
			if (maze[i][j] == WALL) {
				continue;
			}
			if (maze[i][j] == SPACE) {
				continue;
			}

			if (maze[i][j] != myId) {
				if (!hasWallBetween(row, col, i, j, maze)) {
					isTeam = false;
					int id = maze[i][j];
					Entity_Type type = Entity::getEntityByID(id)->getType();
					if (type == SOLDIER) {
						for (it = teamIds.begin(); it != teamIds.end(); it++)
						{
							if (id == *it) { isTeam = true; }
						}
						if (isTeam == true) { setNumVisibleTeam(numVisibleTeam + 1); }
						else {
							setNumVisibleEnemy(numVisibleEnemy + 1);
						}

					}
					targets.push_back(std::make_pair(std::make_pair(maze[i][j], type), std::make_pair(i, j)));
				}
			}


		}
	}
	if (targets.empty()) {
		return false;
	}
	return true;
}

int HasVision::getRoomIndex(Room* rooms, int x, int y) {
	for (int i = 0; i < MAX_ROOMS; i++) {
		if (rooms[i].isCoordinatesInRoom(x, y)) {
			return i;
		}
	}
	return -1; // tunnel
}

bool HasVision::getIsTeamOutGunned() {
	return numVisibleEnemy > numVisibleTeam;
}

