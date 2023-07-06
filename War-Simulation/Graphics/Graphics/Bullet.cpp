#include "Bullet.h"
#include <math.h>
#include "glut.h"
#include <stdio.h>
#include "Soldier.h"

Bullet::Bullet() {

}

Bullet::Bullet(int ownerID)
{
	setOwnerID(ownerID);
}

Bullet::Bullet(double xx, double yy, double alpha)
{
	x = xx;
	y = yy;
	angle = alpha;
	dirx = cos(alpha);
	diry = sin(alpha);

}

Bullet::Bullet(int ownerID,double xx, double yy, double alpha)
{
	x = xx;
	y = yy;
	angle = alpha;
	dirx = cos(alpha);
	diry = sin(alpha);
	setOwnerID(ownerID);

}

bool Bullet::fire(int maze[MSZ][MSZ])
{
	int val = maze[(int)y][(int)x];
	if (val == WALL) {
		setIsFlying(false);
		return false; 
	}
	int myid = getOwnerID();
	Soldier* shooter = Soldier::getSoldierByID(myid);
	if (val != SPACE && val != WALL && val != HEALTH_STORAGE && val != AMMO_STORAGE && val != myid) {

		int damage = getDamage(val);
		
		Soldier* ps = Soldier::getSoldierByID(val);
		if (ps == nullptr) {
			return true;
		}
		if (shooter->isEnemy(ps->getX(), ps->getY())) {
			bool damaged = false;
			if (damaged == false && ps->getIsAlive()) {
				damaged = true;
				int health1 = ps->getHealth();
				doDamage(ps, damage);
				int health2 = ps->getHealth();
				printf("soldier %d lost %d health, left with : %f \n", ps->getID(), health2 - health1, ps->getHealth());
				setIsFlying(false);
				return false;
			}
		}

	}

	setIsFlying(true);
	
	x += dirx * STEP; // move bullet by STEP to direction (dirx,dity)
	y += diry * STEP;
	return true;
}


void Bullet::draw()
{
	double delta = 0.5;
	glColor3d(0, 0, 0); // black
	glBegin(GL_POLYGON);
	
	glVertex2d(x - delta, y);
	glVertex2d(x, y + delta);
	glVertex2d(x + delta, y);
	glVertex2d(x, y - delta);

	/*
	glVertex2d(y - delta, x);
	glVertex2d(y, x + delta);
	glVertex2d(y + delta, x);
	glVertex2d(y, x - delta);
	*/

	glEnd();
}


void Bullet::SimulateFire(int maze[MSZ][MSZ], double security_map[MSZ][MSZ])
{
	while (maze[(int)y][(int)x] != WALL)
	{
		security_map[(int)y][(int)x] += MARK;
		x += dirx * STEP; // move bullet by STEP to direction (dirx,dity)
		y += diry * STEP;

	}
	setIsFlying(false);
	setIsShot(true);
}

int Bullet::getDamage(int id) {
	if (id == getOwnerID()) {
		return 0;
	}
	
	return BULLET_DAMAGE;
}


void Bullet::doDamage(Soldier* ps,int damage) {
	ps->RemoveHealth(damage);
}



