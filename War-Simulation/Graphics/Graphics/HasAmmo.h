#pragma once
#include "Definitions.h"
#include <math.h>

class HasAmmo
{
private:
	int bullets;
	int maxBullets;
	bool isNoAmmo = false;
	bool isLowAmmo = false;

public:
	HasAmmo();
	HasAmmo(int bullets, int maxBullets);
	~HasAmmo();
	
	int getBullets() { return bullets; }
	bool getLowAmmo() { return  bullets < LOW_AMMO_THRESHOLD; }
	bool getNoAmmo() { return bullets == 0; }
	bool getIsNoAmmo() { return isNoAmmo; }
	bool getIsLowAmmo() { return isLowAmmo; }
	int getMaxBullets() { return maxBullets; };

	void setBullets(int b) { bullets = b; }
	void setMaxBullets(int maxB) { maxBullets = maxB; };
	void setIsLowAmmo(bool b) { isLowAmmo = b; }
	void setIsNoAmmo(bool b) { isNoAmmo = b; }

	int RemoveAmmo(int amount);
};


