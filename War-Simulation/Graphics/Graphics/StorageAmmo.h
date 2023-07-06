#pragma once
#include "Definitions.h"
#include "HasAmmo.h"
#include "Entity.h"

class StorageAmmo : public Entity, public HasAmmo
{
public:
	StorageAmmo(int x, int y);
	StorageAmmo(int x, int y, int bullets);

	static StorageAmmo* HSStorages[NUM_AMMO_STORAGES];

	static StorageAmmo* getStorageAmmoByID(int ID) {
		for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
			if (HSStorages[i]->getID() == ID) {
				return HSStorages[i];
			}
		}
		return nullptr;
	}

	static int getStorageAmmoIDByCoordinates(int x, int y) {
		for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
			if (HSStorages[i]->getInitialX() == x && HSStorages[i]->getInitialY() == y) {
				return HSStorages[i]->getID();
			}
		}
		return -1;
	}

	static void setStoragesAmmo(StorageAmmo* hs[NUM_AMMO_STORAGES]) {
		for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
			HSStorages[i] = hs[i];
		}
	}

	int TakeResources(int amount);
};