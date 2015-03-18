#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>

typedef const unsigned int CUNT;
typedef long long int int64;

int64 cache[45] = {0};

int64 spoon(int n) {
	if (cache[n]) {
		return cache[n];
	}

	//printf("calc spoon %d\n", n);

	int64 ret = spoon(n-2) * 2;

	if (n > 4) {
		for (int i = 2; i < n; i += 2) {
			int j = n - i;
			/*if (n==6) {
				printf("s(%d) %d %d\n", n, i, j);
			}*/

			ret += i * j;
		}
	}

	int x = n/2;
	//printf("pow=%d, %d, %d\n", 1L<<x, ret, n);
	ret += 1L<<x;

	cache[n] = ret;

	return ret;
}

int main() {
	freopen("spoon.in", "r", stdin);
#ifndef __APPLE__
	freopen("spoon.out", "w", stdout);
#endif

	cache[2] = 2;

	int N;
	scanf("%d", &N);

	printf("%lld\n", spoon(N));

	return 0;
}