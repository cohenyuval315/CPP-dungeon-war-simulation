#include "HasMobility.h"

HasMobility::HasMobility() {
	setSpeed(0);
	setX(0);
	setY(0);
	setPathIndex(0);
}

HasMobility::HasMobility(double speed) {
	setX(0);
	setY(0);
	setPathIndex(0);
}

HasMobility::HasMobility(int x, int y, double speed)
{
	setX(x);
	setY(y);
	setSpeed(speed);
	setPathIndex(0);
	setStartX(x);
	setStartY(y);
}

HasMobility::~HasMobility()
{
}

void HasMobility::RestorePath(Node* p)
{
	path.clear();
	setPathIndex(0);
	while (p->getParent() != nullptr)
	{
		path.push_back(std::make_pair(p->getRow(), p->getCol()));
		p = p->getParent();
	}

	std::reverse(path.begin(), path.end());
}

void HasMobility::UpdateNeighbor(Node* pneighbor, std::priority_queue <Node*, std::vector<Node*>, CompareNodes>& pq)
{
	std::vector<Node*> tmp;
	Node* pnb;
	while (!pq.empty() && !((*pq.top()) == (*pneighbor)))
	{
		tmp.push_back(pq.top());
		pq.pop();
	}
	if (pq.empty())
	{
		printf("Error: couldn't find gray neighbor in PQ\n");
		exit(1);
	}
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

void HasMobility::AddNeighbor(Node* pcurrent, std::priority_queue <Node*, std::vector<Node*>, CompareNodes>& pq,
	std::vector<Node>& grays, std::vector<Node>& blacks, int direction, int* maze[MSZ])
{
	Node* pneighbor = nullptr;
	double cost = 1;
	std::vector<Node>::iterator it_gray;
	std::vector<Node>::iterator it_black;
	int new_row = pcurrent->getRow();
	int new_col = pcurrent->getCol();
	int tr = pcurrent->getTargetRow();
	int tc = pcurrent->getTargetCol();
	int g = pcurrent->getG();

	switch (direction)
	{
	case UP:
		new_row--;
		break;
	case DOWN:
		new_row++;
		break;
	case LEFT:
		new_col--;
		break;
	case RIGHT:
		new_col++;
		break;
	}
	if (maze[new_row][new_col] != SPACE)
		return;

	pneighbor = new Node(new_row, new_col, tr, tc, pcurrent, g + cost);
	pneighbor->computeF();
	pneighbor->computeH();

	it_gray = find(grays.begin(), grays.end(), *pneighbor);
	it_black = find(blacks.begin(), blacks.end(), *pneighbor);


	if (it_gray == grays.end() && it_black == blacks.end())
	{
		pq.push(pneighbor);
		grays.push_back(*pneighbor);
	}
	else if (it_gray != grays.end())
	{
		if (it_gray->getF() > pneighbor->getF())
		{
			it_gray->setG(pneighbor->getG());
			it_gray->computeF();
			UpdateNeighbor(pneighbor, pq);
		}
	}

}

bool HasMobility::Astar(int* maze[MSZ])
{

	std::priority_queue <Node*, std::vector<Node*>, CompareNodes> pq;
	std::vector<Node> grays;
	std::vector<Node> blacks;
	int r = getX();
	int c = getY();
	int tr = getTargetX();
	int tc = getTargetY();

	if (r == tr && c == tc) {
		return false;
	}
	Node* pn = new Node(r, c, tr, tc, nullptr, 0); // start Node
	Node* pcurrent;
	pq.push(pn);
	grays.push_back(*pn);

	while (!pq.empty())
	{
		pcurrent = pq.top();
		pq.pop();
		if (pcurrent->getH() <= 0.01) // target has been reached
		{
			RestorePath(pcurrent);
			return true;
		}
		else
		{
			if (pcurrent->getRow() > 0)
				AddNeighbor(pcurrent, pq, grays, blacks, UP, maze);
			if (pcurrent->getRow() < MSZ - 1)
				AddNeighbor(pcurrent, pq, grays, blacks, DOWN, maze);
			if (pcurrent->getCol() > 0)
				AddNeighbor(pcurrent, pq, grays, blacks, LEFT, maze);
			if (pcurrent->getCol() < MSZ - 1)
				AddNeighbor(pcurrent, pq, grays, blacks, RIGHT, maze);
		}
	}
	return false;
}

bool HasMobility::Move(int* maze[MSZ], int myId, Room* rooms, bool randomStuck)
{
	if (numStuckPath > 5 && randomStuck) {
		int r = rand() % MAX_ROOMS;
		Room m = rooms[r];
		setTargetX(m.getCenterRow());
		setTargetY(m.getCenterCol());
		Astar(maze);
	}
	if (pathIndex < path.size())
	{
		int row = path[pathIndex].first;
		int col = path[pathIndex].second;
		if (maze[row][col] == SPACE) {
			setCoordinates(row, col, myId, maze);
		}
		int r = getX();
		int c = getY();
		if (r == row && c == col) {
			setPathIndex(pathIndex + 1);
			numStuckPath = 0;
		}
		else {
			numStuckPath += 1;
		}
		return true;
	}
	return false;
}

