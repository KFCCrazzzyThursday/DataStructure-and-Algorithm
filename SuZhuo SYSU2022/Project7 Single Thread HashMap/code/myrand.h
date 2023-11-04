#pragma once
#include <ctime>
#include<vector>
using namespace std;

class myRandom {
private:
	unsigned int seed;

public:
	myRandom() {
		seed =0;
	}
	
	unsigned int mySrand(unsigned int s = (unsigned int)time(NULL));

	unsigned int myRand(); //生成单个伪随机数

	vector<int> myRand(int min, int max);  //生成伪随机序列
};