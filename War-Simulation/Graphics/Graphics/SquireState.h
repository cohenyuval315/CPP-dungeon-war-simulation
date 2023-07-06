#pragma once
#include "State.h"
#include "Squire.h"

class SquireState : public State
{
public:
	virtual void Transform(Squire* ps) = 0; // to the next state
	virtual void OnEnter(Squire* ps) = 0; // to the current state
	virtual void OnExit(Squire* ps) = 0;  // from the current state
	bool operator ==(const SquireState& other) const {
		return this == &other;
	}
};

