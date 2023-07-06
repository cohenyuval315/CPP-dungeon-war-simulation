#include "Entity.h"

Entity* Entity::entities[NUM_ENTITES];

int Entity::IDcounter = 10;

Entity::Entity() {
	setID();
}

Entity::Entity(int x, int y,Entity_Type type) {
	setID();
	setInitialX(x);
	setInitialY(y);
	setType(type);
}
Entity::~Entity() {
}

Entity::Entity(Entity_Type type) {
	setID();
	setType(type);
}
