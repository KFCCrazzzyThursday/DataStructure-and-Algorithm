#include "prime.h"

//������ڵ���x����С����
int prime(int x) {
	int i, j;
	for (i = x; i < 2 * x; i++) {
		for (j = 2; j < i; j++) {
			if (i % j == 0) break;
		}
		if (j == i) return i;
	}
	return 0;
}