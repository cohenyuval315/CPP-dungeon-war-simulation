#include "Patrolling.h"
#include "Attack.h"
#include "Retreat.h"

Patrolling::Patrolling()
{
}


Patrolling::~Patrolling()
{
}

// what will be the NEXT state after GoToForest
void Patrolling::Transform(Soldier* ps)
{

	OnExit(ps);

	ps->Patroll();
	if (ps->getIsEnemyVisible()) {
		ps->setCurrentState(new Attack());
	}
	else {
		if (ps->getIsLowHealth() || ps->getIsLowAmmo()) {
			ps->setCurrentState(new Retreat());
		}
	}
	
}

void Patrolling::OnEnter(Soldier* ps)
{
	
}

void Patrolling::OnExit(Soldier* ps)
{
	//ps->getPath().clear();
}
