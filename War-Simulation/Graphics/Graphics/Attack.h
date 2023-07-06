#pragma once
#include "SoldierState.h"

class Attack: public SoldierState
{
public:
	Attack();
	~Attack();
	void Transform(Soldier* ps);
	void OnEnter(Soldier* ps);
	void OnExit(Soldier* ps);

};