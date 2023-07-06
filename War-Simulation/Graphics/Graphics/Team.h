#pragma once
#include <vector>
#include "Definitions.h"
#include <set>

class Squire;

class NPC;

class Team
{
private:
	int TeamId;
	int TeamSize = 0;
	std::vector<NPC*> members;
	double start_x;
	double end_x;
	double start_y;
	double end_y;
	bool placement = false;


public:
	Squire* squire;
	std::set<std::pair<double, double>> coordinates;
	Team(int TeamId);

	void setTeamId(int id) { TeamId = id; }
	int getTeamId() { return TeamId; }
	void SetTeamSize(int ts) { TeamSize = ts;}
	int getTeamSize() { return TeamSize; }
	void addMember(NPC* s); 

	void setSquire(Squire* s) {
		squire = s;
	}

	std::vector<NPC*> getMembers() { return members; }

	void SetStartX(double x) {start_x = x;}
	void SetStartY(double y) {start_y = y;}
	void SetEndX(double x) {end_x = x;}
	void SetEndY(double y) {end_y= y;}

	double getStartX() {return start_x;}
	double getStartY() {return start_y;}
	double getEndX() {return end_x;}
	double getEndY() {return end_y;}

	void setSpawn(double x_start, double y_start, double x_end, double y_end) {
		SetStartX(x_start);
		SetStartY(y_start);
		SetEndX(x_end);
		SetEndY(y_end);
	}


};

