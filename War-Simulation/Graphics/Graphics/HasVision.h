#pragma once
#include <vector>
#include "Definitions.h"
#include "Node.h"
#include "Entity.h"
#include "Room.h"

class HasVision {

private:
	int visionX = 0;
	int visionY = 0;
	int numVisibleEnemy = 0;
	int numVisibleTeam = 1;
	
	std::vector<std::pair<std::pair<int, Entity_Type>, std::pair<int, int>>> targets;

public:
	HasVision();
	HasVision(int visionX, int visionY);
	HasVision(int visionN);
	~HasVision();
	
	void setVisionN(int n_range) {
		setVisionX(n_range);
		setVisionY(n_range);
	}
	void setVisionY(int y_range) { visionY = y_range; }
	void setVisionX(int x_range) { visionX = x_range; }
	int getVisionY() { return visionY; }
	int getVisionX() { return visionX; }

	void setNumVisibleTeam(int n) { numVisibleTeam = n; }
	int getNumVisibleTeam() { return numVisibleTeam; }

	void setNumVisibleEnemy(int n) { numVisibleEnemy = n; }
	int getNumVisibleEnemy() { return numVisibleEnemy; }

	void setTargets(std::vector<std::pair<std::pair<int, Entity_Type>, std::pair<int, int>>> t) { targets = t; }
	std::vector<std::pair<std::pair<int, Entity_Type>, std::pair<int, int>>>getTargets() { return targets; }

	bool hasWallBetween(int x1, int y1, int x2, int y2, int* maze[MSZ]);
	bool CheckSurrounding(int row, int col, int* maze[MSZ], int myId, std::vector<int> teamIds);
	int getRoomIndex(Room* rooms, int x, int y);
	bool getIsTeamOutGunned();

};