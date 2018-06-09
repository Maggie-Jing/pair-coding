//#include <iostream>
//#include "LiveOperate.h"
//
//#include <gtest/gtest.h>
//
//using namespace std;
//
////#define DEBUG
//
//TEST(Check, Pos00)
//{
//	bool live[5][5] = {
//		{ 0, 0, 1, 0, 0 },
//		{ 0, 1, 1, 0, 1 },
//		{ 1, 0, 0, 1, 0 },
//		{ 0, 1, 0, 0, 1 },
//		{ 1, 0, 0, 1, 0 }
//	};
//
//	vector<vector<bool> > world;
//	for (int i = 0; i < 5; ++i)
//	{
//		vector<bool> temp;
//		for (int j = 0; j < 5; ++j)
//		{
//			temp.push_back(live[i][j]);
//		}
//		world.push_back(temp);
//	}
//
//	LiveOperate lo;
//	lo.init(world, 5, 5);
//
//	EXPECT_EQ(true, lo.checkLive(Point(0, 0)));
//}
//
//TEST(Check, Pos11)
//{
//	bool live[5][5] = {
//		{ 0, 0, 1, 0, 0 },
//		{ 0, 1, 1, 0, 1 },
//		{ 1, 0, 0, 1, 0 },
//		{ 0, 1, 0, 0, 1 },
//		{ 1, 0, 0, 1, 0 }
//	};
//
//	vector<vector<bool> > world;
//	for (int i = 0; i < 5; ++i)
//	{
//		vector<bool> temp;
//		for (int j = 0; j < 5; ++j)
//		{
//			temp.push_back(live[i][j]);
//		}
//		world.push_back(temp);
//	}
//
//	LiveOperate lo;
//	lo.init(world, 5, 5);
//
//	EXPECT_EQ(false, lo.checkLive(Point(1, 1)));
//}
//
//int main(int argc, char* argv[])
//{
//	bool live[5][5] = {
//		{ 0, 0, 1, 0, 0 },
//		{ 0, 1, 1, 0, 1 },
//		{ 1, 0, 0, 1, 0 },
//		{ 0, 1, 0, 0, 1 },
//		{ 1, 0, 0, 1, 0 }
//	};
//
//	vector<vector<bool> > world;
//	for (int i = 0; i < 5; ++i)
//	{
//		vector<bool> temp;
//		for (int j = 0; j < 5; ++j)
//		{
//			temp.push_back(live[i][j]);
//		}
//		world.push_back(temp);
//	}
//
//	LiveOperate lo;
//	lo.init(world, 5, 5);
//	lo.updateLive();
//	lo.showWorld();
//
//	//cout << lo.checkLive(Point(0, 1)) << endl;
//	
//
//#ifdef DEBUG
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//#endif
//
//#ifndef DEBUG
//	return 0;
//#endif
//
//}
