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

	unsigned int myRand(); //���ɵ���α�����

	vector<int> myRand(int min, int max);  //����α�������
};