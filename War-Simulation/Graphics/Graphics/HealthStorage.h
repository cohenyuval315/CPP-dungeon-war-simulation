#pragma once
#include "Definitions.h"
#include "HasHealth.h"
#include "Entity.h"
class HealthStorage : public Entity , public HasHealth
{
public:
	HealthStorage(int x, int y);
	HealthStorage(int x, int y, int health);

	static HealthStorage* HStorages[NUM_HEALTH_STORAGES];

	static HealthStorage* getHealthStorageByID(int ID) {
		for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
			if (HStorages[i]->getID() == ID) {
				return HStorages[i];
			}
		}
		return nullptr;
	}
	static int getHealthStorageIDByCoordinates(int x, int y) {
		for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
			if (HStorages[i]->getInitialX() == x && HStorages[i]->getInitialY() == y) {
				return HStorages[i]->getID();
			}
		}
		return -1;
	}
	static void setHealthStorages(HealthStorage* hs[NUM_HEALTH_STORAGES]) {
		for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
			HStorages[i] = hs[i];
		}
	}


	int TakeResources(int amount);


};


