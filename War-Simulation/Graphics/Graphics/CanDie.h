#pragma once
#include "Definitions.h"


class CanDie
{
private:
	bool isAlive = true;
public:
	CanDie();

	void Die() {
		setIsAlive(false);
	}
	void Revive() {
		setIsAlive(true);
	}
	bool getIsAlive() {
		return isAlive;
	}
	void setIsAlive(bool state) {
		isAlive = state;
	}
};

