#include "HealthStorage.h"



HealthStorage::HealthStorage(int x , int y):Entity(x, y, Entity_Type::HEALTHSTORAGE), HasHealth(MAX_HEALTH_STORAGE_HEALTH,0,MAX_HEALTH_STORAGE_HEALTH) {
	setInitialX(x);
	setInitialY(y);
}

HealthStorage::HealthStorage(int x, int y, int health):Entity(x,y, Entity_Type::HEALTHSTORAGE),HasHealth(health,0, MAX_HEALTH_STORAGE_HEALTH){
	setInitialX(x);
	setInitialY(y);
}



HealthStorage* HealthStorage::HStorages[NUM_HEALTH_STORAGES];


int HealthStorage::TakeResources(int amount) {
	int hp = getHealth();
	int diff = hp - amount;
	if (diff < 0) {
		setHealth(0);
		return hp;
	}
	else {
		setHealth(diff);
		return amount;
	}
}