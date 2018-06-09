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
	void init(vector<vector<bool> > oldWorld, int r, int c);
	void updateLive();
	bool checkLive(Point pos);
	vector<vector<bool> > getWorld();

	void showWorld();
	void LiveOperate::randomInit(int r, int c);

//private:
	vector<vector<bool> > _world;
	int _rows;
	int _cols;
};


