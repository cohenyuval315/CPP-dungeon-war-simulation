#pragma once
#include "Definitions.h"
#include <vector>
#include <queue>
#include "Node.h"
#include "CompareNodes.h"
#include "Utils.h"
#include "Room.h"

class HasMobility
{
private:
	int x;
	int y;
	double realX;
	double realY;
	double speed;
	std::vector<std::pair<int, int>> path;
	int pathIndex = 0;
	int numStuckPath = 0;
	int targetX;
	int targetY;
	int startx = -1;
	int starty = -1;


public:
	HasMobility();
	HasMobility(double speed);
	HasMobility(int x, int y, double speed);
	~HasMobility();

	double getSpeed() { return speed; }
	double getRealX() { return x; }
	double getRealY() { return y; }

	int getX() { return x; }
	int getY() { return y; }

	void setSpeed(double s) { speed = s; }
	void setRealX(double new_x) { realX = new_x; }
	void setRealY(double new_y) { realY = new_y; }

	void setX(int new_x) { x = new_x; }
	void setY(int new_y) { y = new_y; }

	void setCoordinates(int new_x, int new_y, int ID, int* maze[MSZ]) {
		int x = getX();
		int y = getY();
		maze[x][y] = SPACE;
		setX(new_x);
		setY(new_y);
		maze[new_x][new_y] = ID;
	}

	void setTargetX(int x) { 
		targetX = x; 
		path.clear();
	}
	void setTargetY(int y) { 
		targetY = y; 
		path.clear();
	}

	int getTargetX() { return targetX; }
	int getTargetY() { return targetY; }

	int getStartX() { return startx; }
	int getStartY() { return starty; }

	void setStartX(int sx) { startx = sx; }
	void setStartY(int sy) { starty = sy; }

	std::vector<std::pair<int, int>> getPath() { return path; }
	void setPath(std::vector<std::pair<int, int>> p) { path = p; }

	void setPathIndex(int index) { pathIndex = index; }
	int getPathIndex() { return pathIndex; };


	// Astar by current Target X and Target Y
	// clearing and setting path 
	// init path index to 0 
	bool Move(int* maze[MSZ], int myId, Room* rooms, bool randomStuck);

	void RestorePath(Node* p);
	void UpdateNeighbor(Node* pneighbor, std::priority_queue <Node*, std::vector<Node*>, CompareNodes>& pq);
	void AddNeighbor(Node* pcurrent, std::priority_queue <Node*, std::vector<Node*>, CompareNodes>& pq,
		std::vector<Node>& grays, std::vector<Node>& blacks, int direction, int* maze[MSZ]);
	bool Astar(int* maze[MSZ]);


	

};