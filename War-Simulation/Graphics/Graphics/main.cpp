#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <iostream>

#include "glut.h"
#include "HealthStorage.h"
#include "StorageAmmo.h"
#include "Soldier.h"
#include "Grenade.h"
#include "Squire.h"


using namespace std;


Soldier* soldier1;
Soldier* soldier2;
Soldier* soldier3;
Soldier* soldier4;

Squire* squire1;
Squire* squire2;

Soldier* soldiers[NUM_SOLDIERS];
Squire* squires[NUM_SQUIRES];

HealthStorage* healthStorages[NUM_HEALTH_STORAGES];
StorageAmmo* mainAmmoStorages[NUM_AMMO_STORAGES];

Entity* entities[NUM_ENTITES];

int maze[MSZ][MSZ] = { 0 };
double security_map[MSZ][MSZ] = { 0 };
Room rooms[MAX_ROOMS];

const int TEAM1ID= 1;
const int TEAM2ID = 2;

Team* team1 = new Team(TEAM1ID);
Team* team2 = new Team(TEAM2ID);


bool fireBulet = false, throwGrenade = false, isWin = false;
Bullet* pb = nullptr;
Grenade* pg = nullptr;

void InitMaze();
void InitRooms();
void InitTeams();



std::pair<int, int> generateRandomCoordinates(int start_x, int end_x, int start_y, int end_y)
{
	int x, y;
	do
	{
		x = start_x + static_cast<double>(rand()) / RAND_MAX * (end_x - start_x);
		y = start_y + static_cast<double>(rand()) / RAND_MAX * (end_y - start_y);
	} while (maze[x][y] != SPACE);
	return std::make_pair(x, y);
}

std::pair< pair<int, int>, pair<int, int> > generateRandomBlockCoordinates(int start_x, int end_x, int start_y, int end_y, int blocksize)
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
	bool isOk;
	if (end_x - start_x < blocksize || end_y - start_y < blocksize) {
		throw exception("blocks");
	}
	do
	{
		isOk = true;
		int x_start = start_x + static_cast<double>(rand()) / RAND_MAX * (end_x - start_x);
		int y_start = start_y + static_cast<double>(rand()) / RAND_MAX * (end_y - start_y);
		for (int i = 0; i < blocksize; i++) {
			for (int j = 0; j < blocksize; j++) {
				if (maze[i][j] != SPACE) {
					isOk = false;
					break;
				}
			}
		}

	} while (isOk == false);


	return std::make_pair(std::make_pair(x_start, y_start), std::make_pair(x_end, y_end));
}

double* generateColor(int ID) {

	double* color = new double[3];
	color[0] = 0.1; // red
	color[1] = 0.1; // green 
	color[2] = 0.1; // blue
	int teamId = 0;
	Squire* pss = Squire::getSquireByID(ID);
	Soldier* ps = Soldier::getSoldierByID(ID);
	if (pss != nullptr) {

		teamId = pss->getTeamId();
		color[0] = 0.2; // red
		color[1] = 0.2; // green 
		color[2] = 0.2; // blue

	}
	if (ps != nullptr) {
		
		teamId = ps->getTeamId();
		color[0] = 0.3; // red
		color[1] = 0.3; // green 
		color[2] = 0.3; // blue
	}
	color[teamId] = 0.9;
	return color;
}

std::pair<double, double> generateRandomTeamCoordinates(Team* team)
{
	int start_x = team->getStartX();
	int start_y = team->getStartY();
	int end_x = team->getEndX();
	int end_y = team->getEndY();
	double x, y;
	do
	{
		x = start_x + static_cast<double>(rand()) / RAND_MAX * (end_x - start_x);
		y = start_y + static_cast<double>(rand()) / RAND_MAX * (end_y - start_y);
		
	} while (team->coordinates.count({ x, y }) != 0);

	team->coordinates.insert({ x, y });
	return std::make_pair(x, y);
}

void placeTeam(Team* team, Room* rooms, int index) {
	int start_row, end_row, start_col, end_col;
	Room m = rooms[index];
	start_row = m.getCenterRow() - m.getHeight() / 2;
	end_row = m.getCenterRow() + m.getHeight() / 2;
	start_col = m.getCenterCol() - m.getWidth() / 2;
	end_col = m.getCenterCol() + m.getWidth() / 2;
	team->setSpawn(start_row, start_col,end_row, end_col);

	for (int i = 0; i < (int)team->getTeamSize(); ++i)
	{
		std::pair<double, double> result = generateRandomTeamCoordinates(team);
		double x = result.first;
		double y = result.second;
		team->getMembers()[i]->setX(x);
		team->getMembers()[i]->setY(y);

		// initial target position => next room
		
		int initialTargetRoomIndex = index + 1;
		if (initialTargetRoomIndex == MAX_ROOMS) {
			initialTargetRoomIndex = 0;
		}

		int r = rand() % 10;
		//m = rooms[initialTargetRoomIndex];
		m = rooms[r];
		start_row = m.getCenterRow() - m.getHeight() / 2;
		end_row = m.getCenterRow() + m.getHeight() / 2;
		start_col = m.getCenterCol() - m.getWidth() / 2;
		end_col = m.getCenterCol() + m.getWidth() / 2;
		std::pair<int,int> p = generateRandomCoordinates(start_row, end_row, start_col, end_col);
		team->getMembers()[i]->setTargetX(p.first);
		team->getMembers()[i]->setTargetY(p.second);
	}
}




void init()
{
	srand(time(0));
	glClearColor(0, 0.3, 0.0, 0);// color of window background
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // set the coordinates system

	InitMaze();
	InitRooms();
	InitTeams();

}



void InitTeams() {
	
	std::vector<int> team1Ids;
	std::vector<int> team2Ids;
	
	soldier1 = new Soldier();
	soldier1->setMaze(maze);
	soldier1->setSecurityMap(security_map);
	soldier1->setRooms(rooms);

	soldier2 = new Soldier();
	soldier2->setMaze(maze);
	soldier2->setSecurityMap(security_map);
	soldier2->setRooms(rooms);

	soldier3 = new Soldier();
	soldier3->setMaze(maze);
	soldier3->setSecurityMap(security_map);
	soldier3->setRooms(rooms);

	soldier4 = new Soldier();
	soldier4->setMaze(maze);
	soldier4->setSecurityMap(security_map);
	soldier4->setRooms(rooms);

	squire1 = new Squire();
	squire1->setMaze(maze);
	squire1->setSecurityMap(security_map);
	squire1->setRooms(rooms);


	squire2 = new Squire();
	squire2->setMaze(maze);
	squire2->setSecurityMap(security_map);
	squire2->setRooms(rooms);

	soldier1->setTeam(team1, team1->getTeamId());
	soldier2->setTeam(team1,team1->getTeamId());
	team1->addMember(soldier1);
	team1->addMember(soldier2);
	team1->addMember(squire1);
	team1->setSquire(squire1);
	team1Ids.push_back(soldier1->getID());
	team1Ids.push_back(soldier2->getID());
	team1Ids.push_back(squire1->getID());
	soldier1->setTeamIds(team1Ids);
	soldier2->setTeamIds(team1Ids);
	squire1->setTeamIds(team1Ids);
	squire1->setTeamId(team1->getTeamId());
	placeTeam(team1, rooms, 0);

	soldier3->setTeam(team2, team2->getTeamId());
	soldier4->setTeam(team2, team2->getTeamId());
	team2->addMember(soldier3);
	team2->addMember(soldier4);
	team2->addMember(squire2);
	team2->setSquire(squire2);
	team2Ids.push_back(soldier3->getID());
	team2Ids.push_back(soldier4->getID());
	team2Ids.push_back(squire2->getID());
	soldier3->setTeamIds(team2Ids);
	soldier4->setTeamIds(team2Ids);
	squire2->setTeamIds(team2Ids);
	squire2->setTeamId(team2->getTeamId());
	placeTeam(team2, rooms, 1);


	soldiers[0] = soldier1;
	soldiers[1] = soldier2;
	soldiers[2] = soldier3;
	soldiers[3] = soldier4;

	squires[0] = squire1;
	squires[1] = squire2;


	int start_x, end_x, start_y, end_y;
	int i, j, k;
	int height, width, c_col, c_row;
	Room m;
	std::pair<int, int> p1;
	std::pair<int, int> p2;
	for (i = 0; i < MAX_ROOMS; i++) {
		m = rooms[i];
		height = m.getHeight();
		width = m.getWidth();
		c_col = m.getCenterCol();
		c_row = m.getCenterRow();
		start_x = c_row - height / 2;
		end_x = c_row + height / 2;
		start_y = c_col - width / 2;
		end_y = c_col + width / 2;

		for (k = 0; k < NUM_AMMO_STORAGE_PER_ROOM; k++) {
			p2 = generateRandomCoordinates(start_x, end_x, start_y, end_y);
			mainAmmoStorages[i * NUM_AMMO_STORAGE_PER_ROOM + k] = new StorageAmmo(p2.first, p2.second);
			maze[p2.first][p2.second] = AMMO_STORAGE;
		}

		for (j = 0; j < NUM_HEALTH_STORAGE_PER_ROOM; j++) {

			p1 = generateRandomCoordinates(start_x, end_x, start_y, end_y);
			healthStorages[i * NUM_HEALTH_STORAGE_PER_ROOM + j] = new HealthStorage(p1.first, p1.second);
			maze[p1.first][p1.second] = HEALTH_STORAGE;
		}
	}

	
	int s = 0;
	for (i = 0; i < NUM_HEALTH_STORAGES; i++) {
		entities[s] = healthStorages[i];
		s++;
	}
	for (i = 0; i < NUM_AMMO_STORAGES; i++) {
		entities[s] = mainAmmoStorages[i];
		s++;
	}



	entities[s] = soldier1;
	entities[s+1] = soldier2;
	entities[s+2] = soldier3;
	entities[s+3] = soldier4;
	entities[s+4] = squire1;
	entities[s+5] = squire2;
	

	Soldier::setSoldiers(soldiers);
	Squire::setSquires(squires);
	Entity::setEntites(entities);
	HealthStorage::setHealthStorages(healthStorages);
	StorageAmmo::setStoragesAmmo(mainAmmoStorages);


	for (i = 0; i < NUM_SOLDIERS; i++) {
		Soldier* p = soldiers[i];
		int id = p->getID();
		int x = p->getX();
		int y = p->getY();
		printf("soldier %d ,pos: (%d,%d)\n", id, x, y);
	}
	for (i = 0; i < NUM_SQUIRES; i++) {
		Squire* p = squires[i];
		int id = p->getID();
		int x = p->getX();
		int y = p->getY();
		printf("squire %d ,pos: (%d,%d)\n", id, x, y);
	}
	soldier1->init();
	soldier2->init();
	soldier3->init();
	soldier4->init();
	squire1->init();
	squire2->init();

}

void InitMaze()
{
	int i, j;
	for (i = 0; i < MSZ; i++)
		for (j = 0; j < MSZ; j++)
			maze[i][j] = WALL;

}

bool IsOverlapping(int cx, int cy, int h, int w, int room_index)
{
	int i, dx, dy;
	for (i = 0; i < room_index; i++)
	{
		dx = fabs(cx - rooms[i].getCenterCol());
		dy = fabs(cy - rooms[i].getCenterRow());
		if (dx < w / 2 + rooms[i].getWidth() / 2 + 4 && dy < h / 2 + rooms[i].getHeight() / 2 + 4)
			return true;
	}
	return false;
}

void DrawRooms()
{
	int i, r, c;
	int start_row, end_row, start_col, end_col;
	for (i = 0; i < MAX_ROOMS; i++)
	{
		start_row = rooms[i].getCenterRow() - rooms[i].getHeight() / 2;
		end_row = rooms[i].getCenterRow() + rooms[i].getHeight() / 2;
		start_col = rooms[i].getCenterCol() - rooms[i].getWidth() / 2;
		end_col = rooms[i].getCenterCol() + rooms[i].getWidth() / 2;
		for (r = start_row; r <= end_row; r++)
			for (c = start_col; c <= end_col; c++)
				maze[r][c] = SPACE;
	}
}

void CreateSecurityMap()
{
	int counter = 0, x, y, xx, yy;

	for (counter = 0; counter < 2500; counter++)
	{
		x = rand() % W;
		y = rand() % H;
		xx = MSZ * (x) / (double)W;
		yy = MSZ * (y) / (double)H;
		if (maze[yy][xx] == SPACE)
		{
			pg = new Grenade(xx, yy);
			pg->SimulateExplosion(maze, security_map);
		}
	}
}

void UpdateNeighbor(Node* pneighbor, priority_queue <Node*, vector<Node*>, CompareNodes>& pq)
{
	vector<Node*> tmp;
	Node* pnb;
	//	while (!pq.empty() && !(pq.top()->getRow() == pneighbor->getRow() && pq.top()->getCol() == pneighbor->getCol()))
	while (!pq.empty() && !((*pq.top()) == (*pneighbor)))
	{
		tmp.push_back(pq.top());
		pq.pop();
	}
	if (pq.empty()) // this shouldn't happen
	{
		cout << "Error: couldn't find gray neighbor in PQ\n";
		exit(1);
	}
	// pneighbor has been found, so we have to update it
	pnb = pq.top();
	pq.pop();
	pnb->setG(pneighbor->getG());
	pnb->computeF();
	pq.push(pnb);

	while (!tmp.empty())
	{
		pq.push(tmp.back());
		tmp.pop_back();
	}
}

void AddNeighbor(Node* pcurrent, priority_queue <Node*, vector<Node*>, CompareNodes>& pq,
	vector<Node>& grays, vector<Node>& blacks, int direction)
{
	Node* pneighbor = nullptr;
	double cost;
	vector<Node>::iterator it_gray;
	vector<Node>::iterator it_black;


	switch (direction)
	{
	case UP:
		if (maze[pcurrent->getRow() - 1][pcurrent->getCol()] == WALL)
			cost = WALL_COST;
		else cost = SPACE_COST;
		pneighbor = new Node(pcurrent->getRow() - 1, pcurrent->getCol(), pcurrent->getTargetRow(),
			pcurrent->getTargetCol(), pcurrent, pcurrent->getG() + cost);
		break;
	case DOWN:
		if (maze[pcurrent->getRow() + 1][pcurrent->getCol()] == WALL)
			cost = WALL_COST;
		else cost = SPACE_COST;
		pneighbor = new Node(pcurrent->getRow() + 1, pcurrent->getCol(), pcurrent->getTargetRow(),
			pcurrent->getTargetCol(), pcurrent, pcurrent->getG() + cost);
		break;
	case LEFT:
		if (maze[pcurrent->getRow()][pcurrent->getCol() - 1] == WALL)
			cost = WALL_COST;
		else cost = SPACE_COST;
		pneighbor = new Node(pcurrent->getRow(), pcurrent->getCol() - 1, pcurrent->getTargetRow(),
			pcurrent->getTargetCol(), pcurrent, pcurrent->getG() + cost);
		break;
	case RIGHT:
		if (maze[pcurrent->getRow()][pcurrent->getCol() + 1] == WALL)
			cost = WALL_COST;
		else cost = SPACE_COST;
		pneighbor = new Node(pcurrent->getRow(), pcurrent->getCol() + 1, pcurrent->getTargetRow(),
			pcurrent->getTargetCol(), pcurrent, pcurrent->getG() + cost);
		break;
	}

	// check the status of a new neighbor
	it_gray = find(grays.begin(), grays.end(), *pneighbor);
	it_black = find(blacks.begin(), blacks.end(), *pneighbor);

	if (it_gray == grays.end() && it_black == blacks.end()) // this is a WHITE Node
	{
		pq.push(pneighbor);
		grays.push_back(*pneighbor);
	}
	else if (it_gray != grays.end())
	{
		if (it_gray->getF() > pneighbor->getF()) // pneighbor is BETTER
		{
			it_gray->setG(pneighbor->getG());
			it_gray->computeF();
			UpdateNeighbor(pneighbor, pq);
		}
	}

}

void RestorePath(Node* p)
{
	while (p->getParent() != nullptr)
	{
		if (maze[p->getRow()][p->getCol()] == WALL)
			maze[p->getRow()][p->getCol()] = SPACE;

		p = p->getParent();
	}
}

void DigTunnel(int startIndex, int endIndex)
{
	priority_queue <Node*, vector<Node*>, CompareNodes> pq;
	vector<Node> grays; 
	vector<Node> blacks;
	int r, c, tr, tc;
	r = rooms[startIndex].getCenterRow();
	c = rooms[startIndex].getCenterCol();
	tr = rooms[endIndex].getCenterRow();
	tc = rooms[endIndex].getCenterCol();
	Node* pn = new Node(r, c, tr, tc, nullptr, 0); // start Node
	Node* pcurrent;
	pq.push(pn);
	grays.push_back(*pn);

	while (!pq.empty())
	{
		pcurrent = pq.top();
		pq.pop();
		if (pcurrent->getH() <= 0.1) // target has been reached
		{
			RestorePath(pcurrent);
			return;
		}
		else
		{
			if (pcurrent->getRow() > 0)
				AddNeighbor(pcurrent, pq, grays, blacks, UP);
			if (pcurrent->getRow() < MSZ - 1)
				AddNeighbor(pcurrent, pq, grays, blacks, DOWN);
			if (pcurrent->getCol() > 0)
				AddNeighbor(pcurrent, pq, grays, blacks, LEFT);
			if (pcurrent->getCol() < MSZ - 1)
				AddNeighbor(pcurrent, pq, grays, blacks, RIGHT);
		}
	}
}

void CreateTunnels()
{
	for (int i = 0; i < MAX_ROOMS; i++)
	{
		for (int j = i + 1; j < MAX_ROOMS; j++)
			DigTunnel(i, j);
		cout << "room " << i << " is finished\n";
	}
}

void InitRooms()
{
	int i, h, w, cx, cy;
	for (i = 0; i < MAX_ROOMS; i++)
	{
		do
		{
			cx = 14 + rand() % (MSZ - 28);
			cy = 14 + rand() % (MSZ - 28);
			h = 8 + rand() % 12;
			w = 8 + rand() % 12;
		} while (IsOverlapping(cx, cy, h, w, i));
		// set the parameters
		rooms[i].setCenterRow(cy);
		rooms[i].setCenterCol(cx);
		rooms[i].setHeight(h);
		rooms[i].setWidth(w);
	}
	DrawRooms();
	CreateTunnels();
}

void DrawMaze()
{
	int i, j;
	for (i = 0; i < MSZ; i++) {
		for (j = 0; j < MSZ; j++)
		{
			double c = 1 - security_map[i][j];
			switch (maze[i][j])
			{
			case SPACE:
				//				glColor3d(0.9, 0.9, 0.9); // light gray
				glColor3d(c, c, c);
				break;
			case WALL:
				glColor3d(0.3, 0.3, 0.3); // dark gray
				break;
			case AMMO_STORAGE:
				glColor3d(0.0, 0.0, 0.0); 
				break;
			case HEALTH_STORAGE:
				glColor3d(0.9, 0.1, 0.1); // dark gray
				break;
			default:
				int id = maze[i][j];
				double* color = generateColor(id);
				glColor3d(color[0], color[1], color[2]);
				delete[] color;
				break;
			}

			// draw square
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();

		}
	}
}









bool checkIfWin() {
	bool win = false;
	int team1NumAlive = NUM_SOLDIERS / 2;
	int team2NumAlive = NUM_SOLDIERS / 2;

	for (int i = 0; i < NUM_SOLDIERS; i++) {

		if (soldiers[i]->getIsAlive() == false) {
			if (soldiers[i]->getTeamId() == TEAM1ID) {
				team1NumAlive -= 1;
			}
			if (soldiers[i]->getTeamId() == TEAM2ID) {
				team2NumAlive -= 1;
			}
		}
	}
	if (team1NumAlive == 0) {
		printf("game ended team 2 has won! \n");
		return true;
	}
	else {
		if (team2NumAlive == 0) {
			printf("game ended team 1 has won! \n");
			return true;
		}
	}
	return false;
}


bool s1 = true;
bool s2 = true;
bool s3 = true;
bool s4 = true;
bool s5 = true;
bool s6 = true;


void Actions() {

	if (s1 == true) {
		s1 = soldier1->DoAction(maze);
	}

	if (s2 == true) {
		s2 = soldier2->DoAction(maze);
	}

	if (s3 == true) {
		s3 = soldier3->DoAction(maze);
	}

	if (s4 == true) {
		s4 = soldier4->DoAction(maze);
	}
	if (s5 == true) {
		s5 = squire1->DoAction(maze);
	}
	if (s6 == true) {
		s6 = squire2->DoAction(maze);
	}
	
}

void startNPCS() {
	soldier1->start();
	soldier2->start();
	soldier3->start();
	soldier4->start();
	squire1->start();
	squire2->start();
}

void stopNPCS() {
	soldier1->stop();
	soldier2->stop();
	soldier3->stop();
	soldier4->stop();
	squire1->stop();
	squire2->stop();
}

void freeAll() {

	for (int i = 0; i < NUM_HEALTH_STORAGES; i++) {
		//healthStorages[i]->free();
		delete healthStorages[i];
	}
	for (int i = 0; i < NUM_AMMO_STORAGES; i++) {
		//mainAmmoStorages[i]->free();
		delete mainAmmoStorages[i];
	}
	for (int i = 0; i < NUM_SOLDIERS; i++) {
		soldiers[i]->free();
		delete soldiers[i];
	}
	for (int i = 0; i < NUM_SQUIRES; i++) {
		//squires[i]->free();
		delete squires[i];
	}
	delete team1;
	delete team2;
}










void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawMaze();
	if (pb != nullptr)
		pb->draw();
	if (pg != nullptr)
		pg->draw();

	
	if (soldier1 != nullptr)
		soldier1->draw();
	if (soldier2 != nullptr)
		soldier2->draw();
	if (soldier3 != nullptr)
		soldier3->draw();
	if (soldier4 != nullptr)
		soldier4->draw();
	if (squire1 != nullptr)
		squire1->draw();
	if (squire2 != nullptr)
		squire2->draw();

	glViewport(0, H - 20, 150, 20);

	// Draw the label
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 150, 0, 50);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	const char* team1Text = "Team 1 | Team 2";
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(5.0f, 5.0f);
	for (int i = 0; team1Text[i] != '\0'; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, team1Text[i]);
	}


	const int color_rect_size = 20;
	const int color_rect_x_offset = 40;
	const int color_rect_y_offset = 30;
	const int row_spacing = 30;

	// draw first row of rectangles
	glColor3f(0.0f, 1.0f, 0.0f); // green
	const int s1_y = MSZ - 60;
	glRectf(color_rect_x_offset, s1_y - color_rect_y_offset, color_rect_x_offset + color_rect_size, s1_y - color_rect_y_offset - color_rect_size);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glRasterPos2f(color_rect_x_offset + color_rect_size / 2 - 4, s1_y - color_rect_y_offset - color_rect_size / 2 - 6); // adjust position to center the number
	const char* s1_green = "2";
	for (int i = 0; s1_green[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s1_green[i]);
	}
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glRectf(color_rect_x_offset * 2, s1_y - color_rect_y_offset, color_rect_x_offset * 2 + color_rect_size, s1_y - color_rect_y_offset - color_rect_size);
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glRasterPos2f(color_rect_x_offset * 2 + color_rect_size / 2 - 4, s1_y - color_rect_y_offset - color_rect_size / 2 - 6); // adjust position to center the number
	const char* s1_red = "1";
	for (int i = 0; s1_red[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s1_red[i]);
	}







	// draw second row of rectangles
	glColor3f(1.0f, 1.0f, 0.0f); // yellow
	glRectf(color_rect_x_offset, color_rect_y_offset - 3 * row_spacing, color_rect_x_offset + color_rect_size, color_rect_y_offset - 4*row_spacing);
	glColor3f(0.0f, 0.0f, 0.0f); // black
	glRasterPos2f(color_rect_x_offset + color_rect_size / 2 - 4, color_rect_y_offset - 7* row_spacing / 2 - 6); // adjust position to center the number
	const char* s2_yellow = "3";
	for (int i = 0; s2_yellow[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s2_yellow[i]);
	}

	glColor3f(1.0f, 0.5f, 0.0f); // orange
	glRectf(color_rect_x_offset * 2, color_rect_y_offset - 3*row_spacing, color_rect_x_offset * 2 + color_rect_size, color_rect_y_offset - 4*row_spacing);
	glColor3f(0.0f, 0.0f, 0.0f); // black
	glRasterPos2f(color_rect_x_offset * 2 + color_rect_size / 2 - 4, color_rect_y_offset - 7*row_spacing / 2 - 6); // adjust position to center the number
	const char* s2_orange = "4";
	for (int i = 0; s2_orange[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s2_orange[i]);
	}




	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// Reset the viewport to cover the entire window
	glViewport(0, 0, W, H);

	glutSwapBuffers(); // show all
}

void idle()
{
	if (isWin) {
		exit(1);
	}
	else {
		isWin = checkIfWin();
	}

	Actions();
	if (pb != nullptr && fireBulet)
		fireBulet = pg->explode(maze);


	if (pg != nullptr && throwGrenade) {
		throwGrenade = pg->explode(maze);
	}

	if (soldier1->getFireBullet()) {
		soldier1->setFireBullet(soldier1->explodeBarrell(maze));
	}
	if (soldier2->getFireBullet()) {
		soldier2->setFireBullet(soldier2->explodeBarrell(maze));
	}
	if (soldier3->getFireBullet()) {
		soldier3->setFireBullet(soldier3->explodeBarrell(maze));
	}
	if (soldier4->getFireBullet()) {
		soldier4->setFireBullet(soldier4->explodeBarrell(maze));
	}


	glutPostRedisplay(); // indirect call to display
}

void menu(int choice)
{
	switch (choice)
	{
	case 1: 
		fireBulet = true;
		break;
	case 2: // throw grenade
		throwGrenade = true;
		break;
	case 3:
		CreateSecurityMap();
		break;
	case 4:
		startNPCS();
		break;
	case 5:
		stopNPCS();
		break;
	}

}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		pb = new Bullet(MSZ * x / (double)W, MSZ * (H - y) / (double)H, (rand() % 360) * PI / 180.0);
		pg = new Grenade(MSZ * x / (double)W, MSZ * (H - y) / (double)H);
		double winY = ((double)MSZ - (double)soldier1->getX()) * (double)H / (double)MSZ;
		double winX = (double)soldier1->getY() * (double)H / (double)MSZ;
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(400, 50);
	glutCreateWindow("Game");
	//init2D(0.0f, 0.0f, 0.0f);
	glutDisplayFunc(display); // display is the refresh function
	glutIdleFunc(idle);
	glutMouseFunc(mouse);

	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Fire bullet", 1);
	glutAddMenuEntry("Throw grenade", 2);
	glutAddMenuEntry("Show Security Map", 3);
	glutAddMenuEntry("Start Npcs", 4);
	glutAddMenuEntry("Stop Npcs", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	try
	{
		init();
		glutMainLoop();
	}
	catch (const std::exception&)
	{
		freeAll();
	}



	return 0;
}
