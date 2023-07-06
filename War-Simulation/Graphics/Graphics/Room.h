#pragma once
class Room
{
private:
	int centerRow, centerCol, height, width;
public:
	Room();
	Room(int centerRow, int centerCol, int height, int width);
	~Room();

	int getCenterRow() { return centerRow; }
	int getCenterCol() { return centerCol; }
	int getHeight() { return height; }
	int getWidth() { return width; }
	void setCenterRow(int r) { centerRow = r; }
	void setCenterCol(int c) { centerCol = c; }
	void setHeight(int h) { height = h; }
	void setWidth(int w) { width = w; }

	bool isCoordinatesInRoom(int x, int y) {
		int start_row, end_row, start_col, end_col;
		start_row = getCenterRow() - getHeight() / 2;
		end_row = getCenterRow() + getHeight() / 2;
		start_col = getCenterCol() - getWidth() / 2;
		end_col = getCenterCol() + getWidth() / 2;
		if (x < start_row)return false;
		if (x > end_row) return false;
		if (y < start_col) return false;
		if (y > end_col) return false;
		return true;
	}

};

