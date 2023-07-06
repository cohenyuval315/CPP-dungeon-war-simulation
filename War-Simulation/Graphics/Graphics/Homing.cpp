#include "Homing.h"
#include "SearchResources.h"

Homing::Homing() {

}
Homing::~Homing() {

}

void Homing::OnEnter(Squire* ps) {

}

void Homing::Transform(Squire* ps) {
	OnExit(ps);

	ps->GoToBase();
	if (ps->getHealth() < ps->getMaxHealth()) {
		ps->setCurrentState(new SearchResources());
	}else
	if (ps->getBullets() < ps->getMaxBullets()) {
		ps->setCurrentState(new SearchResources());
	}
}

void Homing::OnExit(Squire* ps) {

}

