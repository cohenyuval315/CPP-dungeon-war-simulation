#include "SearchResources.h"
#include "Homing.h"

void SearchResources::OnEnter(Squire* ps) {

}

SearchResources::SearchResources()
{
}

SearchResources::~SearchResources()
{
}

void SearchResources::Transform(Squire* ps) {
	OnExit(ps);

	ps->SearchResources();

	if (ps->getMaxHealth() == ps->getHealth() && ps->getMaxBullets() == ps->getBullets()) {
		ps->setCurrentState(new Homing());
	}
	
}

void SearchResources::OnExit(Squire* ps) {
	
}

