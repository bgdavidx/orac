#include <cstdio>
#include <cstdlib>
#include <map>

const int MAX_N = 100001;

int indexes[MAX_N];

int main() {
	freopen("pairin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("pairout.txt", "w", stdout);
#endif

	int N;
	scanf("%d", &N);

	int max = 0;

	for (int i = 1; i <= 2*N; i++) {
		int x;
		scanf("%d", &x);

		if (indexes[x] != 0) {
			int z = i - indexes[x];

			if (z > max) {
				max = z;
			}
		} else {
			indexes[x] = i;
		}
	}

	printf("%d\n", max);

	return 0;
}