#pragma once
#ifndef SQUIRE_H
#define SQUIRE_H
#include "NPC.h"
#include "Utils.h" 
#include "Storage.h"

class SquireState;

class Squire : public NPC
{
private:
	bool isGotAmmo = true;
	bool isGotHealth = true;
	bool isInBase = true;
	SquireState* pCurrentState = nullptr;
	Node* currentNode;



public:
	static Squire* squires[NUM_SQUIRES];
	
	static void setSquires(Squire* s[NUM_SQUIRES]) {
		for (int i = 0; i < NUM_SQUIRES; i++) {
			squires[i] = s[i];
		}
	}

	static Squire* getSquireByID(int ID) {
		for (int i = 0; i < NUM_SQUIRES; i++) {
			if (squires[i]->getID() == ID) {
				return squires[i];
			}
		}
		return nullptr;
	}

	explicit Squire();
	explicit Squire(int x, int y);
	~Squire();

	void setCurrentState(SquireState* s) { pCurrentState = s; }
	SquireState* getCurrentState() { return pCurrentState; }



	bool DoAction(int maze[MSZ][MSZ]);
	void init();
	void draw();

	void SearchResources();
	void GoToBase();

	bool setClosestStorage(Entity_Type type);
	void takeResource(int x, int y, Entity* ps);
	Entity_Type PrioritizeResourceType();
	int _takeHealth(HealthStorage* ps, int amount);
	int _takeAmmo(StorageAmmo* ps, int amount);




};
#endif 