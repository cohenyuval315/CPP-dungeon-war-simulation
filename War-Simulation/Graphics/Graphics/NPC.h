#pragma once
#include <typeinfo>
#include <vector>
#include <utility>
#include "Definitions.h"
#include "Entity.h"
#include "HasMobility.h"
#include "HasHealth.h"
#include "HasAmmo.h"
#include "Team.h"
#include "Room.h"
#include "Utils.h"
#include "HasVision.h"
#include "HealthStorage.h"
#include "StorageAmmo.h"

class NPC : public Entity, public HasMobility , public HasAmmo, public HasHealth, public HasVision
{
private:
	bool isRun = false;
	bool isAmmoResourcesExists = true;
	bool isHealthResourcesExists = true;
	bool noMore = false;


	int* maze[MSZ];
	double* security_map[MSZ];
	Room* rooms;
	Team* team;
	int teamId;
	std::vector<int> teamIds;


public:
	explicit NPC();
	explicit NPC(double speed, Entity_Type type, int start_bullets, int max_bullets, int start_health, double LowHealthThreshold, int maxHealth, int vision_x, int vision_y);
	explicit NPC(int x, int y, double speed, Entity_Type type);
	explicit NPC(int x, int y, double speed, Entity_Type type, int start_bullets, int max_bullets, int start_health, double LowHealthThreshold, int maxHealth, int vision_x, int vision_y);
	~NPC();

	bool getIsRun() { return isRun; }
	void setIsRun(bool b) { isRun = b; }

	void setIsAmmoResourcesExists(bool b) { isAmmoResourcesExists = b; }
	bool getIsAmmoResourcesExists() { return isAmmoResourcesExists; }

	void setIsHealthResourcesExists(bool b) { isHealthResourcesExists = b; }
	bool getIsHealthResourcesExists() { return isHealthResourcesExists; }

	void setNoMore(bool b) { noMore = b; }
	bool getNoMore() { return noMore; }

	void start();
	void stop();




	bool CheckAmmoStorages();
	bool CheckHealthStorages();
	void CheckStorages();


	// getters
	double** getSecurityMap() { return security_map; }
	
	int** getMaze() { return maze; }
	
	Room* getRooms() { return rooms; }
	
	Team* getTeam() { return team; }
	
	int getTeamId() { return teamId; };
	
	std::vector<int> getTeamIds() {return teamIds;}
	
	Squire* getTeamSquire() {return getTeam()->squire;}


	//setters
	void setTeamIds(std::vector<int> ts) { teamIds = ts; }

	void setMaze(int m[MSZ][MSZ]) {
		for (int i = 0; i < MSZ; i++) {
			maze[i] = m[i];
		}
	}

	void setSecurityMap(double sm[MSZ][MSZ]) {
		for (int i = 0; i < MSZ; i++) {
			security_map[i] = sm[i];
		}
	}

	void setRooms(Room rms[MAX_ROOMS]) { rooms = rms; }

	void setTeam(Team* t,int tid) { 
		team = t; 
		setTeamId(tid);
	}

	void setTeamId(int tid) { teamId = tid; };



	
};