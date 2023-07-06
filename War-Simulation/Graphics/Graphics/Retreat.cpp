#include "Retreat.h"
#include "Patrolling.h"
#include "Attack.h"

Retreat::Retreat()
{
}


Retreat::~Retreat()
{

}

void Retreat::Transform(Soldier* ps)
{
	OnExit(ps);
	
	ps->Retreat();

	if (!ps->getIsEnemyVisible() && !ps->getIsLowHealth() && !ps->getIsLowAmmo()) {
		ps->setCurrentState(new Patrolling());
	}

	
}

void Retreat::OnEnter(Soldier* ps)
{

}

void Retreat::OnExit(Soldier* ps)
{
}
