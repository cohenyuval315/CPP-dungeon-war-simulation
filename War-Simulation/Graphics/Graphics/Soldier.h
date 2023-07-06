#pragma once

#include "Definitions.h"
#include "NPC.h"
#include "CanDie.h"
#include "Bullet.h"

class SoldierState;


class Soldier: public NPC, public CanDie
{
private:
	bool isOutGunned = false;
	bool isNoAmmo = false;
	bool isLowAmmo = false;
	bool isLowHealth = false;
	bool isEnemyVisible = false;
	bool onYourOwn = false;
	bool isSquireAmmoResource = true;
	bool isSquireHealthResource = true;
	bool fireBullet = false;


	SoldierState* pCurrentState = nullptr;
	Node* currentNode;
	Bullet* bp = nullptr;





public:
	static Soldier* soldiers[NUM_SOLDIERS];
	static void setSoldiers(Soldier* s[NUM_SOLDIERS]) {
		for (int i = 0; i < NUM_SOLDIERS; i++) {
			soldiers[i] = s[i];
		}
	}
	static Soldier* getSoldierByID(int ID) {
		for (int i = 0; i < NUM_SOLDIERS; i++) {
			if (soldiers[i]->getID() == ID) {
				return soldiers[i];
			}
		}
		return nullptr;
	}
	Soldier();
	Soldier(int x, int y);
	~Soldier();
	bool DoAction(int m[MSZ][MSZ]);

	void setCurrentState(SoldierState* s) { pCurrentState = s; }	
	SoldierState* getCurrentState() { return pCurrentState; }

	bool getIsEnemyVisible() { return isEnemyVisible; }
	void setIsEnemyVisible(bool b) { isEnemyVisible = b;}

	bool getIsSquireHealthResource() { return isSquireHealthResource; }
	bool getIsSquireAmmoResource() { return isSquireAmmoResource; }
	void setIsSquireHealthResource(bool b) { isSquireHealthResource = b; }
	void setIsSquireAmmoResource(bool b) { isSquireAmmoResource = b; }

	bool getIsLowHealth() { return isLowHealth; }
	void setIsLowHealth(bool b) { isLowHealth = b; }

	bool getIsOutGunned() { return isOutGunned; }
	void setIsOutGunned(bool b) { isOutGunned = b; }

	void setFireBullet(bool b) { fireBullet = b; }
	bool getFireBullet() { return fireBullet; }

	void setIsOnYourOwn(bool b) { onYourOwn = b; }
	bool getIsOnYourOwn() { return onYourOwn; }


	std::pair<int, int> getEnemy();
	bool isEnemy(int x, int y);


	void init();

	void Retreat();
	void Attack();
	void Patroll();

	void checkSquireResources();
	void isOnYourOwn();
	void checkEnemiesSurrounding();
	void checkIfOutGunned();
	void CheckHealth();
	void CheckAmmo();


	bool explodeBarrell(int maze[MSZ][MSZ]);
	void draw();
	void free();

};


