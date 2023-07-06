#include "HasHealth.h"

HasHealth::HasHealth()
{

}

HasHealth::HasHealth(double health, double lowHealthThreshold, double maxHealth)
{
	setHealth(health);
	setHealthThreshold(lowHealthThreshold);
	setMaxHealth(maxHealth);
}

HasHealth::~HasHealth()
{

}


double HasHealth::RemoveHealth(double amount) {
	double h = health - amount;
	if (h < 0) {
		setHealth(0);
		return health;
	}
	setHealth(h);
	return amount;
}