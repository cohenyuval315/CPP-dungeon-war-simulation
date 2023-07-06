#include "HasAmmo.h"

HasAmmo::HasAmmo()
{
}

HasAmmo::HasAmmo(int bullets, int maxBullets) {
	setBullets(bullets);
	setMaxBullets(maxBullets);
}

HasAmmo::~HasAmmo()
{
}

int HasAmmo::RemoveAmmo(int amount) {
	bullets = bullets - amount;
	if (bullets < 0) {
		bullets = 0;
		return bullets;
	}
	return amount;
}