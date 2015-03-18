#include <cstdio>
#include <cstdlib>

#define MAX_N 50001

int N, P;
int students[MAX_N];
int sums[MAX_N];
int maxes[MAX_N];
int ans = 0;

inline int max(int a, int b) { printf("\tmax(%d, %d)\n", a, b); return a > b ? a : b; }

int main() {
	freopen("trainin.txt", "r", stdin);
	//freopen("trainout.txt", "w", stdout);

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &students[i]);
	}

	scanf("%d", &P);

	int firstSum = 0;

	for (int i = 0; i < P; i++) {
		firstSum += students[i];
	}

	sums[0] = firstSum;

	printf("sum[0]=%d\n", sums[0]);
 
	for (int i = 1; i <= N - P; i++) {
		firstSum -= students[i - 1];
		firstSum += students[i + P - 1];

		sums[i] = firstSum;

		printf("sum[%d]=%d\n", i, sums[i]);
	}

	/*for (int i = 0; i < N - P * 2; i++) {
		for (int j = i + P; j < N - P; j++) {
			for (int k = j + P; k < N; k++) {
				ans = max(ans, sums[i] + sums[j] + sums[k]);
				//printf("best=%d, %d, %d\n", i, j, k);
			}
		}
	}*/
	for (int i = 0; i < N; i++) {
		maxes[i] = sums[i];

		printf("maxes[%d]=%d\n", i, maxes[i]);
	}

	printf("\n");

	for (int i = P; i < N; i++) {
		maxes[i] = max(maxes[i - P] + sums[i], maxes[i]);

		printf("maxes[%d]=%d\n", i, maxes[i]);
	}

	// 75, 60, 105

	printf("\n");

	int ans = 0;

	for (int i = P * 2; i < N; i++) {
		maxes[i] = max(maxes[i - P * 2] + sums[i], maxes[i]);

		printf("maxes[%d]=%d\n", i, maxes[i]);

		ans = max(ans, maxes[i]);
	}

	printf("%d\n", ans);

	return 0;
}