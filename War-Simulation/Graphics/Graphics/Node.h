#pragma once
class Node
{
private:
	Node* parent;
	int row, col, target_row, target_col;
	double g, h, f;

public:
	Node();
	Node(int r, int c, int tr, int tc, Node* p, double new_g);
	~Node();
	void computeH();
	void computeF() { f = g + h; }

	void setG(int value) { g = value; }
	void setH(int value) { h = value; }

	double getF() { return f; }
	double getH() { return h; }
	double getG() { return g; }

	int getRow() { return row; }
	int getCol() { return col; }
	int getTargetRow() { return target_row; }
	int getTargetCol() { return target_col; }
	Node* getParent() { return parent; }
	void setParent(Node* p) { parent = p; }


	
	bool operator ==(const Node& other) { return other.row == row && other.col == col; }

};

