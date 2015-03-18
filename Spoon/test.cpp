#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

#include "family.h"

typedef const unsigned int CUNT;

CUNT INF = 999999999;

int N;
int *array;
int st[16000];

int makeST(int ss, int se, int si) {
	if (ss == se) {
		st[si] = array[ss];
		return array[ss];
	}

	int mid = ss+(se-ss)/2;
	st[si] = std::min(makeST(ss, mid, si*2+1), makeST(mid+1, se, si*2+2));

	return st[si];
}

int findMin(int ss, int se, int qs, int qe, int index) {
	if (qs <= ss && qe >= se) {
		return st[index];
	}

	if (se < qs || ss > qe) {
		return INF;
	}

	int mid = ss+(se-ss)/2;

	return std::min(findMin(ss, mid, qs, qe, 2*index+1),
			findMin(mid+1, se, qs, qe, 2*index+2));
}

int main() {
	N = getNumElements();
	array = getElementArray();

    makeST(0, N-1, 0);


    int a, b;
    while (getNextQuery(&a, &b)) {
        
        haveSolution(findMin(0, N-1, a, b, 0));
    }
    return 0;
}