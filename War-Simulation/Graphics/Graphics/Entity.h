#pragma once
#include "Definitions.h"

enum Entity_Type;

class Entity
{
private:
	static int IDcounter;
	int ID;

	Entity_Type type;

public:
	int initial_x;
	int initial_y;
	static Entity* entities[NUM_ENTITES];
	Entity();
	Entity(Entity_Type type);
	Entity(int x, int y, Entity_Type type);
	~Entity();

	static void setEntites(Entity** en) { 
		for (int i = 0; i < NUM_ENTITES; i++) {
			entities[i] = en[i];
		}
	}

	static Entity* getEntityByID(int ID) {
		for (int i = 0; i < NUM_ENTITES; i++) {
			if (entities[i]->getID() == ID) {
				return entities[i];
			}
		}
		return nullptr;
	}

	Entity_Type getType() { return type; }
	void setType(Entity_Type t) { type = t; }
	void setID() {ID = ++IDcounter;}
	void setInitialX(int x) {initial_x = x;}
	void setInitialY(int y) {initial_y = y;}
	int getInitialX() {return initial_x;}
	int getInitialY() {return initial_y;}
	int getID() {return ID;}
};
