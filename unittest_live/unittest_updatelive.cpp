#include <gtest/gtest.h>
#include "LiveOperate.h"

TEST(testUpdate, myUpdatetest)
{
	bool live[5][5] = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0 }
	};

	vector<vector<bool> > world;
	for (int i = 0; i < 5; ++i)
	{
		vector<bool> temp;
		for (int j = 0; j < 5; ++j)
		{
			temp.push_back(live[i][j]);
		}
		world.push_back(temp);
	}

	LiveOperate lo;
	lo.init(world, 5, 5);

	EXPECT_EQ(true, lo.checkLive(Point(1, 1)));
}