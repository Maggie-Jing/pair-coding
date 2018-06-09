#include "LiveOperate.h"
#include <iostream>
using namespace std;

LiveOperate::LiveOperate()
{
}


LiveOperate::~LiveOperate()
{
}

void LiveOperate::init(vector<vector<bool> > oldWorld, int r, int c)
{
	_world = oldWorld;
	_rows = r;
	_cols = c;
}
void LiveOperate::updateLive()
{
	vector<vector<bool> > new_wold;
	for (int r = 0; r < _rows; ++r)
	{
		vector<bool> temp;
		for (int c = 0; c < _cols; ++c)
		{
			Point pos(r, c);
			temp.push_back(checkLive(pos));
		}
		new_wold.push_back(temp);
	}
	//更新旧世界：
	_world = new_wold;
}


bool LiveOperate::checkLive(Point pos)
{
	int alive_sum = 0;
	for (int j = pos.y - 1; j <= pos.y + 1 && j < _rows; ++j)
	{
		if (j < 0)
		{
			continue;
		}
		
		for (int i = pos.x - 1; i <= pos.x + 1 && i < _cols; ++i)
		{
			if (i < 0)
			{
				continue;
			}
			
			if (_world[i][j])
			{
				alive_sum++;
			}
		}
	}
	if (_world[pos.x][pos.y])
	{
		alive_sum -= 1;
	}
	if (alive_sum <= 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LiveOperate::showWorld()
{
	for (int i = 0; i < _cols; ++i)
	{
		for (int j = 0; j < _rows; ++j)
		{
			cout << _world[i][j] << " ";
		}
		cout << endl;
	}
}

void LiveOperate::randomInit(int r, int c) {
	_rows = r;
	_cols = c;
	srand((unsigned)time(NULL));	
	vector<vector<bool> > new_world;	
	for (int i = 0; i < _cols; ++i) {
		vector<bool> temp_vec;		
		for (int j = 0; j < _rows; ++j)
		{ 
			int temp = rand() % 2;			
			temp_vec.push_back(temp);
		}
			new_world.push_back(temp_vec);
	}
	_world = new_world;
}

vector<vector<bool> > LiveOperate::getWorld() {

	return _world;
}