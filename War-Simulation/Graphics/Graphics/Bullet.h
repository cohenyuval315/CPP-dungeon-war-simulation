#pragma once
#include "Definitions.h"





class Soldier;
class Bullet
{
private:
	double x, y;
	double dirx, diry;
	double angle;
	bool isFlying = false;
	bool isShot = false;
	int ownerID;
	

public:
	
	Bullet();
	Bullet(int ownerID);
	Bullet(int ownerID,double xx, double yy, double alpha);
	Bullet(double xx, double yy, double alpha);

	double getX(){
		return x;
	}
	double getY() {
		return y;
	}
	double getDirX() {
		return dirx;
	}
	double getDirY() {
		return diry;
	}
	double getAngle() {
		return angle;
	}
	void setX(double nx){
		x = nx;
	}
	void setY(double nx) {
		x = nx;
	}
	void setAngle(double nx) {
		x = nx;
	}
	void setDirY(double nx) {
		x = nx;
	}
	void setDirX(double nx) {
		x = nx;
	}
	bool getIsShot() {
		return isShot;
	}
	void setIsShot(bool b) {
		isShot = b;
	}
	void setIsFlying(bool b) {
		isFlying = b;
	}

	void setOwnerID(int id) { ownerID = id; }
	int getOwnerID() { return ownerID; }

	bool fire(int maze[MSZ][MSZ]);
	void draw();
	bool getIsFlying() { return isFlying; }
	void SimulateFire(int maze[MSZ][MSZ], double security_map[MSZ][MSZ]);
	int getDamage(int id);
	void doDamage(Soldier* ps, int damage);
};

