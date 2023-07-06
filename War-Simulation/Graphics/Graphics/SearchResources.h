#pragma once
#ifndef SEARCH
#define SEARCH
#include "SquireState.h"
class Squire;

class SearchResources :
	public SquireState
{
public:
	SearchResources();
	~SearchResources();
	void Transform(Squire* ps);
	void OnEnter(Squire* ps);
	void OnExit(Squire* ps);
};

#endif 