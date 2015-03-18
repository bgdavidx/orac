#include <cstdio>
#include <cstdlib>

#define MAX_N 1001

int N, M;
int itemSizes[MAX_N];
int itemValues[MAX_N];

int bestValues[MAX_N];
int bestItems[MAX_N];
int bestSizes[MAX_N];

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
	freopen("knapin.txt", "r", stdin);
	freopen("knapout.txt", "w", stdout);

	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &itemSizes[i], &itemValues[i]);
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 0; j < N; j++) {
			int itemSize = itemSizes[j];
			int itemValue = itemValues[j];

			if (itemSize <= i) {
				//bestValues[i] = max(bestValues[i], bestValues[i - itemSize] + itemValue);
				int bestNow = bestValues[i];
				int possibleNewBest = bestValues[i - itemSize] + itemValue;

				if (possibleNewBest > bestNow) {
					bestItems[i] = j + 1;
					bestValues[i] = possibleNewBest;
					bestSizes[i] = itemSize;
				}
			}
		}
	}

	//printf("%d\n", bestValues[M]);

	int nowSize = M;

	while (nowSize > 0) {
		printf("%d\n", bestItems[nowSize]);
		nowSize -= bestSizes[nowSize];

		if (bestSizes[nowSize] == 0) {
			break;
		}
	}

	return 0;
}