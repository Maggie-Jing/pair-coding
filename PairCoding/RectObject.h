#pragma once
class RectObject
{
public:
	int x = 0;
	int y = 0;
	int length = 50;
	bool life = false;
	bool child_life = false;
	//int color[2] = {};

	
	RectObject();
	~RectObject();
	void _setLife();
	void _setChildLife(bool my_life);

};

