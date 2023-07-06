#pragma once
#include "Definitions.h"

class HasHealth
{
private:
	double health;
	double lowHealthThreshold;
	double maxHealth;

public:
	HasHealth();
	HasHealth(double health, double lowHealthThreshold, double maxHealth);
	~HasHealth();

	double getHealth() { return health; }
	void setHealth(double h) { health = h; }
	double getHealthThreshold() { return lowHealthThreshold; }
	void setHealthThreshold(double threshold) { lowHealthThreshold = threshold; }

	double getMaxHealth() { return maxHealth; }
	void setMaxHealth(double max) { maxHealth = max; }

	bool getIsLowHP() { return health < lowHealthThreshold; }
	
	double RemoveHealth(double amount);




};


