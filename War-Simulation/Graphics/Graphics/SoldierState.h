#pragma once
#include "State.h"
#include "Soldier.h"

class SoldierState: public State
{
public:
	virtual void Transform(Soldier* ps) = 0;
	virtual void OnEnter(Soldier* ps) = 0;
	virtual void OnExit(Soldier* ps) = 0;
	bool operator ==(const SoldierState& other) const {
		return this == &other;
	}
};

