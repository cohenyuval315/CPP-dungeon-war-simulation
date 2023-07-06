#pragma once

const int W = 600; // window Width
const int H = 600; // window Height

const int MSZ = 100;

const int BLACK = 4;
const int GRAY = 5;
const int PATH = 6;

const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

const double WALL_COST = 20;
const double SPACE_COST = 1;
const double PI = 3.14;

const int MAX_SOLDIER_BULLETS= 10;
const int MAX_SOLDIER_HEALTH = 100;
const int START_SOLDIER_BULLETS = 5;
const int START_SOLDIER_HEALTH = 100;



const int MAX_SPUIRE_BULLETS = 10;
const int MAX_SPUIRE_HEALTH_POINTS = 10;
const int START_SPUIRE_BULLETS = 10;
const int START_SPUIRE_HEALTH_POINTS = 10;


const int MAX_AMMO_STORAGE_BULLETS = 10;
const int MAX_HEALTH_STORAGE_HEALTH = 10;

const double LOW_HEALTH_THRESHOLD = 30;
const double LOW_AMMO_THRESHOLD = 5;

const double SQUIRE_SPEED = 0.1;
const double SOLDIER_SPEED = 0.1;



const int SPACE = 0;
const int WALL = 1;
const int DEAD = 2;
const int AMMO_STORAGE = 45;
const int HEALTH_STORAGE = 46;


const int NUM_SOLDIERS = 4;
const int NUM_SQUIRES = 2;
const int MAX_ROOMS = 10;

const int VISION_N = 10;
const int SOLDIER_VISION_Y = VISION_N;
const int SOLDIER_VISION_X = VISION_N;
const int SQUIRE_VISION_X = VISION_N;
const int SQUIRE_VISION_Y = VISION_N;


const int  NUM_HEALTH_STORAGE_PER_ROOM = 2;
const int  NUM_AMMO_STORAGE_PER_ROOM = 2;

const int NUM_HEALTH_STORAGES = MAX_ROOMS * NUM_HEALTH_STORAGE_PER_ROOM;
const int NUM_AMMO_STORAGES = MAX_ROOMS * NUM_AMMO_STORAGE_PER_ROOM;
const int NUM_ENTITES = NUM_AMMO_STORAGE_PER_ROOM * MAX_ROOMS + NUM_HEALTH_STORAGE_PER_ROOM * MAX_ROOMS + NUM_SQUIRES + NUM_SOLDIERS;

enum Entity_Type {
	SOLDIER,
	SQUIRE,
	HEALTHSTORAGE,
	AMMOSTORAGE,
};

const double STEP = 0.2;
const double MARK = 0.001;
const int BULLET_DAMAGE = 5;