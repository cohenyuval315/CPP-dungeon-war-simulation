#include "StorageAmmo.h"


StorageAmmo::StorageAmmo(int x, int y) :Entity(x, y, Entity_Type::AMMOSTORAGE), HasAmmo(MAX_AMMO_STORAGE_BULLETS, MAX_AMMO_STORAGE_BULLETS) {

}

StorageAmmo::StorageAmmo(int x, int y, int bullets) :Entity(x, y, Entity_Type::AMMOSTORAGE), HasAmmo(bullets,MAX_AMMO_STORAGE_BULLETS) {
}



StorageAmmo* StorageAmmo::HSStorages[NUM_AMMO_STORAGES];


int StorageAmmo::TakeResources(int amount) {
	int hp = getBullets();
	int diff = hp - amount;
	if (diff < 0) {
		setBullets(0);
		return hp;
	}
	else {
		setBullets(diff);
		return amount;
	}
}
