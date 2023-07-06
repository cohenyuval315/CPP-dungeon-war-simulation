#pragma once
#ifndef HOMING
#define HOMING

#include "SquireState.h"

class Squire;

class Homing : public SquireState
{
public:
	Homing();
	~Homing();
	void Transform(Squire* ps);
	void OnEnter(Squire* ps);
	void OnExit(Squire* ps);
};

#endif // SEARCH_H