#pragma once
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

struct Point {
	int x;
	int y;
	Point(int x, int y) :x(x), y(y) {}
};

class LiveOperate
{
public:
	LiveOperate();
	~LiveOperate();

public:
	void init(int r, int c);
	void updateLive();
	bool checkLive(Point pos);
	bool getWorld(int x, int y);
	int getRows();
	void setRows(int rows);
	int getCols();
	void setCols(int cols);

	void showWorld();
	void randomInit();

private:
	void clear();
private:
	int** _world;
	int _rows;
	int _cols;
};


