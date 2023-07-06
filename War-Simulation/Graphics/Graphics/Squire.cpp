#include "Squire.h"
#include "Homing.h"

Squire* Squire::squires[NUM_SQUIRES];

Squire::Squire(int x, int y):NPC(x,y,SQUIRE_SPEED, Entity_Type::SQUIRE,START_SPUIRE_BULLETS, MAX_SPUIRE_BULLETS,START_SPUIRE_HEALTH_POINTS, 0, MAX_SPUIRE_HEALTH_POINTS,SQUIRE_VISION_X, SQUIRE_VISION_Y)
{
	pCurrentState = new Homing();
	pCurrentState->OnEnter(this);
	
}

Squire::Squire() :NPC(SQUIRE_SPEED, Entity_Type::SQUIRE,START_SPUIRE_BULLETS,MAX_SPUIRE_BULLETS,START_SPUIRE_HEALTH_POINTS,0,MAX_SPUIRE_HEALTH_POINTS,SQUIRE_VISION_X, SQUIRE_VISION_Y)
{
	pCurrentState = new Homing();
	pCurrentState->OnEnter(this);
}

Squire::~Squire() {

}


void Squire::init() {
	int r = getX();
	int c = getY();
	int tr = getTargetX();
	int tc = getTargetY();
	Node* pn = new Node(r, c, tr, tc, nullptr, 0);
	currentNode = pn;
	int id = getID();
	getMaze()[r][c] = id;
	Astar(getMaze());
}

void Squire::draw() {

}

bool Squire::DoAction(int maze[MSZ][MSZ]) {
	if (!getIsRun()) {
		return true;
	}
	if (getNoMore()  && getHealth() == 0 && getBullets() == 0) {
		maze[getX()][getY()] = SPACE;
		return false;
	}
	CheckStorages();

	pCurrentState->Transform(this);
	return true;
}


bool Squire::setClosestStorage(Entity_Type type) {
	int size = (NUM_AMMO_STORAGE_PER_ROOM + NUM_HEALTH_STORAGE_PER_ROOM) * MAX_ROOMS;
	int min_distance = -1;
	int tx;
	int ty;
	int index = -1;
	int targetX = -1;
	int targetY = -1;
	if (type == HEALTHSTORAGE) {
		HealthStorage** hs = HealthStorage::HStorages;
		for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
			if (hs[i]->getHealth() == 0) {
				continue;
			}
			tx = hs[i]->getInitialX();
			ty = hs[i]->getInitialY();

			double dis = Utils::EuclideanDistance(tx, ty, getX(), getY());
			index = i;
			if (min_distance < dis) {
				min_distance = dis;
				targetX = tx;
				targetY = ty;
			}

		}
	}
	if (type == AMMOSTORAGE) {
		StorageAmmo** hss = StorageAmmo::HSStorages;
		for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
			if (hss[i]->getBullets() > 0) {
				continue;
			}
			tx = hss[i]->getInitialX();
			ty = hss[i]->getInitialY();

			double dis = Utils::EuclideanDistance(tx, ty, getX(), getY());
			index = i;
			if (min_distance < dis) {
				min_distance = dis;
				targetX = tx;
				targetY = ty;
			}
		}
	}

	if (min_distance == -1 || index == -1 || targetX == -1 || targetY == -1) {
		return false;
	}

	setTargetX(tx);
	setTargetY(ty);
	return true;
}

void Squire::takeResource(int x, int y, Entity* ps) {
	if (ps->getType() == HEALTHSTORAGE) {

		int hp = getHealth();
		int maxHP = getMaxHealth();
		int amount = _takeHealth((HealthStorage*)ps, maxHP - hp);
		setHealth(getHealth() + amount);
	}

	if (ps->getType() == AMMOSTORAGE) {
		int bullets = getBullets();
		int maxBullets = getMaxBullets();
		int amount = _takeAmmo((StorageAmmo*)ps, maxBullets - bullets);
		setBullets(getBullets() + amount);

	}
}

Entity_Type Squire::PrioritizeResourceType() {
	double d1 = (getBullets() - getMaxBullets()) / getMaxBullets();
	double d2 = (getHealth() - getMaxHealth()) / getMaxHealth();
	if (d2 < d1) {
		return HEALTHSTORAGE;
	}
	return AMMOSTORAGE;
}

int Squire::_takeHealth(HealthStorage* ps, int amount) {
	return ps->TakeResources(amount);
}

int Squire::_takeAmmo(StorageAmmo* ps, int amount) {
	return ps->TakeResources(amount);
}

void Squire::SearchResources() {
	if (!Move(getMaze(), getID(), getRooms(), true)) {
		int x = getX();
		int y = getY();
		Entity_Type type = PrioritizeResourceType();
		if (setClosestStorage(type) == -1) {
			return;
		}
		int tx = getTargetX();
		int ty = getTargetY();

		if ((x == tx + 1 && y == ty + 1) ||
			(x == tx - 1 && y == ty + 1) ||
			(x == tx && y == ty + 1) ||
			(x == tx + 1 && y == ty) ||
			(x == tx - 1 && y == ty) ||
			(x == tx && y == ty) ||
			(x == tx + 1 && y == ty - 1) ||
			(x == tx - 1 && y == ty - 1) ||
			(x == tx && y == ty - 1)) {
			if (type == HEALTHSTORAGE) {
				takeResource(tx, ty, HealthStorage::getHealthStorageByID(HealthStorage::getHealthStorageIDByCoordinates(x, y)));
			}
			if (type == AMMOSTORAGE) {
				takeResource(tx, ty, StorageAmmo::getStorageAmmoByID(StorageAmmo::getStorageAmmoIDByCoordinates(x, y)));
			}
			return;
		}

		Astar(getMaze());

	}
}

void Squire::GoToBase() {
	int x = getX();
	int y = getY();
	int tx = getInitialX();
	int ty = getInitialY();
	if (tx == x && ty == y) {
		return;
	}
	else {
		setTargetX(tx);
		setTargetY(ty);
		Move(getMaze(), getID(), getRooms(), false);
	}
}
