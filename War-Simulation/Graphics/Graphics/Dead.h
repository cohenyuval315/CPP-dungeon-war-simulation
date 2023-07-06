#pragma once
#include "SoldierState.h"

class Dead : public SoldierState
{
public:
	Dead();
	~Dead();
	void Transform(Soldier* ps);
	void OnEnter(Soldier* ps);
	void OnExit(Soldier* ps);

};