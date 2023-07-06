#include "Attack.h"
#include "Patrolling.h"
#include "Retreat.h"

Attack::Attack()
{
}


Attack::~Attack()
{
}

void Attack::Transform(Soldier* ps)
{
	OnExit(ps);
	ps->Attack();

	if (!ps->getIsEnemyVisible()) {
		ps->setCurrentState(new Patrolling());
	}

	if (ps->getIsSquireAmmoResource() || ps->getIsSquireHealthResource()) {


		if (ps->getIsLowHealth()) {

			if (ps->getIsOutGunned()) {
				ps->setCurrentState(new Retreat());
			}

		}
		else
			if (ps->getIsNoAmmo()) {
				ps->setCurrentState(new Retreat());
			}
			else
				if (ps->getIsOutGunned()) {
					if (ps->getIsLowHealth()) {
						ps->setCurrentState(new Retreat());
					}
				}
	}


}

void Attack::OnEnter(Soldier* ps)
{
}

void Attack::OnExit(Soldier* ps)
{
	//ps->setEnemyVisible();
}
