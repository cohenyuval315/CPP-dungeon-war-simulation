#pragma once
#include "SoldierState.h"

class Retreat : public SoldierState
{
public:
	Retreat();
	~Retreat();
	void Transform(Soldier* ps);
	void OnEnter(Soldier* ps);
	void OnExit(Soldier* ps);

};