#include "myrand.h"

#define RANDOM_MAX 32767


unsigned int myRandom::mySrand(unsigned int s) {
	seed = s;
	return s;
}

unsigned int myRandom::myRand() {
	seed = (seed * 31 + 13) % RANDOM_MAX;
	return seed;
}

vector<int> myRandom::myRand(int min, int max) {
	vector<int> v(max-min+1);
	for (int i = 0; i < max - min + 1; ++i) {
		v[i] = i + min;
	}
	for (int i = 0; i < max-min+1; i++) {
		int j = myRand() % (max - min + 1 - i) + i;
		int temp = v[i];
		v[i] = v[j];
		v[j] = temp;
	}
	return v;
}
