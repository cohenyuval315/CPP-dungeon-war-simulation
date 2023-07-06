#include "NPC.h"
//#include "Team.h"

NPC::NPC() :Entity(), HasMobility() ,HasHealth(), HasAmmo(), HasVision() {
	setTargetX(0);
	setTargetY(0);
} 

NPC::NPC(int x, int y, double speed, Entity_Type type):Entity(x, y,type), HasMobility(x, y, speed), HasHealth(), HasAmmo(), HasVision() {
	setTargetX(0);
	setTargetY(0);

}

NPC::NPC(int x, int y, double speed, Entity_Type type, int start_bullets, int max_bullets, int start_health, double LowHealthThreshold, int maxHealth, int vision_x, int vision_y) : Entity(x, y, type), HasMobility(x, y, speed), HasHealth(start_health, LowHealthThreshold, maxHealth), HasAmmo(start_bullets, max_bullets), HasVision(vision_x, vision_y) 
{
	setTargetX(0);
	setTargetY(0);
}

NPC::NPC(double speed, Entity_Type type, int start_bullets, int max_bullets, int start_health, double LowHealthThreshold, int maxHealth, int vision_x, int vision_y) : Entity(type), HasMobility(speed), HasHealth(start_health, LowHealthThreshold, maxHealth), HasAmmo(start_bullets, max_bullets), HasVision(vision_x, vision_y){
	setTargetX(0);
	setTargetY(0);
}


NPC::~NPC() {
	setTargetX(0);
	setTargetY(0);
}

void NPC::start() {
	setIsRun(true);
	int id = getID();
	printf("NPC %d starting\n", id);
}

void NPC::stop() {
	setIsRun(false);
	int id = getID();
	printf("NPC %d stopping\n", id);
}


bool NPC::CheckAmmoStorages() {
	StorageAmmo** hs = StorageAmmo::HSStorages;
	for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
		if (hs[i]->getBullets() > 0) {
			return true;
		}
	}
	return false;
}

bool NPC::CheckHealthStorages() {
	HealthStorage** hs = HealthStorage::HStorages;
	for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
		if (hs[i]->getHealth() > 0) {
			return true;
		}
	}
	return false;
}

void NPC::CheckStorages() {
	bool a = CheckAmmoStorages();
	bool b = CheckHealthStorages();
	if (a == true) {
		setIsAmmoResourcesExists(true);
	}
	else {
		setIsAmmoResourcesExists(false);
	}
	if (b == true) {
		setIsHealthResourcesExists(true);
	}
	else {
		setIsHealthResourcesExists(false);
	}
	if (a && b == false) {
		setNoMore(true);
	}
	else {
		setNoMore(false);
	}


}
