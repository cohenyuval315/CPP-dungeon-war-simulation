#include "Soldier.h"
#include "Patrolling.h"

Soldier* Soldier::soldiers[NUM_SOLDIERS];

Soldier::Soldier(int x , int y) : NPC(x, y, SOLDIER_SPEED, Entity_Type::SOLDIER, START_SOLDIER_BULLETS, MAX_SOLDIER_BULLETS,START_SOLDIER_HEALTH, LOW_HEALTH_THRESHOLD,MAX_SOLDIER_HEALTH, SOLDIER_VISION_X, SOLDIER_VISION_Y), CanDie()
{
	pCurrentState = new Patrolling();
	pCurrentState->OnEnter(this);
}


Soldier::Soldier() : NPC(SOLDIER_SPEED, Entity_Type::SOLDIER, START_SOLDIER_BULLETS, MAX_SOLDIER_BULLETS, START_SOLDIER_HEALTH, LOW_HEALTH_THRESHOLD, MAX_SOLDIER_HEALTH, SOLDIER_VISION_X, SOLDIER_VISION_Y), CanDie()
{
	pCurrentState = new Patrolling();
	pCurrentState->OnEnter(this);
}

Soldier::~Soldier() {
}

bool Soldier::DoAction(int m[MSZ][MSZ]) {
	if (!getIsRun()) {
		return true;
	}
	if (!getIsAlive()) {
		m[getX()][getY()] = SPACE;
		return false;
	}

	if (getFireBullet()) {
		setFireBullet(explodeBarrell(m));
	}

	CheckSurrounding(getX(), getY(), getMaze(), getID(), getTeamIds());
	checkSquireResources();
	isOnYourOwn();
	checkEnemiesSurrounding();
	checkIfOutGunned();
	CheckHealth();
	CheckAmmo();
	CheckStorages();

	pCurrentState->Transform(this);
	return true;
}

void Soldier::init() {
	int r = getX();
	int c = getY();
	int tr = getTargetX();
	int tc = getTargetY();
	Node* pn = new Node(r, c, tr, tc, nullptr, 0);
	currentNode = pn;
	int** maze = getMaze();
	maze[r][c] = getID();
	Astar(maze);
}


std::pair<int, int> Soldier::getEnemy() {
	int ex, ey, eid;
	Entity_Type type;
	std::pair<int, int> p;
	if (getNumVisibleEnemy() == 0) {
		p = std::make_pair(-1, -1);
		return p;
	}
	else {
		std::vector<std::pair<std::pair<int, Entity_Type>, std::pair<int, int>>> targets = getTargets();
		for (int i = 0; i < targets.size(); i++) {

			ey = targets[i].second.second;
			ex = targets[i].second.first;
			eid = targets[i].first.first;
			type = targets[i].first.second;
			if (type == SOLDIER) {
				if (isEnemy(ex, ey)) {
					if (getSoldierByID(eid)->getIsAlive()) {
						p = std::make_pair(ex, ey);
						return p;
					}
				}
			}
		}
	}
	p = std::make_pair(-1, -1);
	return p;
}


bool Soldier::isEnemy(int x, int y) {
	int** maze = getMaze();
	int id = maze[x][y];

	int teamId = getTeamId();
	Soldier* ps = getSoldierByID(id);
	if (ps == nullptr) {
		return false;
	}
	int eeTeamId = ps->getTeamId();
	return teamId != eeTeamId;
}

void Soldier::Retreat() {
	NPC* pss = (NPC*)getTeamSquire();

	int sid = pss->getID();
	int tx = pss->getX();
	int ty = pss->getY();

	int x = getX();
	int y = getY();
	bool isNext = false;

	if (getMaze()[x + 1][ty] == sid) {
		isNext = true;
	}
	if (getMaze()[x - 1][ty] == sid) {
		isNext = true;
	}
	if (getMaze()[x][ty + 1] == sid) {
		isNext = true;
	}
	if (getMaze()[x][ty - 1] == sid) {
		isNext = true;
	}

	if (isNext == true) {

		int maxHp = getMaxHealth();
		int health = getHealth();
		int maxBullets = getMaxBullets();
		int bullets = getBullets();
		int hp_diff = maxHp - health;
		int bullet_diff = maxBullets - bullets;
		setBullets(getBullets() + pss->RemoveAmmo(bullet_diff));
		setHealth(getHealth() + pss->RemoveHealth(hp_diff));
		//printf("took resource pre = hp:%d b:%d,  now : hp:%f b:%d\n", health, bullets, getHealth(), getBullets());
	}
	else {
		int txx = tx;
		int tyy = ty;
		if (getMaze()[tx + 1][ty] == SPACE) {
			txx = tx + 1;
		}
		if (getMaze()[tx - 1][ty] == SPACE) {
			txx = tx - 1;
		}
		if (getMaze()[tx][ty + 1] == SPACE) {
			tyy = ty + 1;
		}
		if (getMaze()[tx][ty - 1] == SPACE) {
			tyy = ty - 1;
		}
		setTargetX(txx);
		setTargetY(tyy);
		Astar(getMaze());
		Move(getMaze(), getID(), getRooms(), true);
	}


}

void Soldier::Attack() {
	if (fireBullet == true) {
		return;
	}
	if (getBullets() == 0) {
		return;
	}
	std::pair<int, int> e = getEnemy();
	int ex = e.first;
	int ey = e.second;
	if (ex == -1 && ey == -1) {
		return;
	}
	int x = getX();
	int y = getY();
	int id = getID();
	double alpha = Utils::getAlpha(y, x, ey, ex);
	bp = new Bullet(id, (double)y, (double)x, alpha);
	setFireBullet(true);
	setBullets(getBullets() - 1);
}

void Soldier::Patroll() {
	if (!Move(getMaze(), getID(), getRooms(), true)) {
		int x = getX();
		int y = getY();
		int tx = getTargetX();
		int ty = getTargetY();


		if (x == tx && y == ty) { // patroll next room

			// 
			int j = getRoomIndex(getRooms(), x, y);
			int i = j + 1;
			if (i >= MAX_ROOMS) {
				i = 0;
			}
			//Room rm = getRooms()[i];


			int r = rand() % 10;
			Room rm = getRooms()[r];

			tx = rm.getCenterRow();
			ty = rm.getCenterCol();
			int width = rm.getWidth();
			int height = rm.getHeight();
			std::pair<int, int> cord = Utils::generateRandomCoordinates(tx + height / 2, tx - height / 2, ty + width / 2, ty - width / 2, getMaze());
			setTargetX(tx);
			setTargetY(ty);
		}
		Astar(getMaze());

	}
}


void Soldier::checkSquireResources() {
	NPC* pss = (NPC*)getTeamSquire();

	if (pss->getHealth() > 0) {
		setIsSquireHealthResource(true);
	}
	else {
		setIsSquireHealthResource(false);
	}
	if (pss->getBullets() > 0) {
		setIsSquireAmmoResource(true);
	}
	else {
		setIsSquireAmmoResource(false);
	}
}

void Soldier::isOnYourOwn() {
	bool s1 = getIsSquireAmmoResource();
	bool s2 = getIsSquireHealthResource();
	bool s3 = getIsAmmoResourcesExists();
	bool s4 = getIsHealthResourcesExists();
	if (s1 == s2 == s3 == s4 == false) {
		setIsOnYourOwn(true);
	}
	else {
		setIsOnYourOwn(false);
	}
}

void Soldier::checkEnemiesSurrounding() {
	if (getNumVisibleEnemy() > 0) {
		setIsEnemyVisible(true);
	}
	else {
		setIsEnemyVisible(false);
	}
}

void Soldier::checkIfOutGunned() {
	if (getIsTeamOutGunned()) {
		setIsOutGunned(true);
	}
	else {
		setIsOutGunned(false);
	}
}

void Soldier::CheckHealth() {
	if (getIsLowHP()) {
		if (getHealth() == 0) {
			setIsAlive(false);
			Die();
		}
		else {
			setIsAlive(true);
		}
		setIsLowHealth(true);
	}
	else {
		setIsLowHealth(false);
	}
}

void Soldier::CheckAmmo() {
	if (getLowAmmo()) {
		setIsLowAmmo(true);
		if (getNoAmmo()) {
			setIsNoAmmo(true);
		}
		else {
			setIsNoAmmo(false);
		}
	}
	else {
		setIsLowAmmo(false);
	}
}



bool Soldier::explodeBarrell(int maze[MSZ][MSZ])
{
	bool finished = true;
	if (bp->fire(maze)) {
		finished = false;
		setFireBullet(false);
	}

	return !finished;
}

void Soldier::draw() {
	if (bp != nullptr) {
		bp->draw();
	}
}

void Soldier::free() {
	delete bp;
	delete currentNode;
	delete pCurrentState;
}

