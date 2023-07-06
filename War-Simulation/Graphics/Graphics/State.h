#pragma once

class State
{
private:
	//vector<Condition> conditions;
public:
	//void setConditions(vector<Condition> conds) { conditions = conds; }
	//vector<Condition> getConditions() { return conditions; }
	bool operator ==(const State& other) const {
		return this == &other;
	}
};

