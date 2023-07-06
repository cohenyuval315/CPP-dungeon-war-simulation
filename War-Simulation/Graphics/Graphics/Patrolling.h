#pragma once
#include "SoldierState.h"

class Patrolling : public SoldierState
{
public:
	Patrolling();
	~Patrolling();
	void Transform(Soldier* ps) ; 
	void OnEnter(Soldier* ps); 
	void OnExit(Soldier* ps) ; 
};