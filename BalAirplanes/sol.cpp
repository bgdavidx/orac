#include <cstdio>
#include <cstdlib>

#define MAX_SUM 60001
#define MAX_N 1000

char summable[MAX_SUM] = {0};
char w1[MAX_N] = {0};
int w[MAX_N] = {0};
int prev[MAX_SUM] = {0};

int main() {
	freopen("balin.txt", "r", stdin);
	freopen("balout.txt", "w", stdout);

	int sum = 0, N;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &w[i]);
		//summable[w[i]] = true;
		sum += w[i];
	}

	summable[0] = true;

	
	for (int j = 0; j < N; j++) {
		//printf("Processing: %d\n", w[j]);
		for (int i = sum/2; i >= w[j]; i--) {
			if (summable[i - w[j]]) {
				if (!summable[i]) {
					prev[i] = w[j];
					//printf("prev[%d]=%d\n", i, w[j]);
				}
				summable[i] = true;
				
				//printf("%d is reachable\n", i);
			}
		}
	}

	int minDiff = MAX_SUM;
	int bestWeight = 0;

	for (int i = 1; i <= sum/2; i++) {
		if (summable[i]) {
			//printf("%d is reachable\n", i);

			int diff = abs(sum - i * 2);

			if (diff < minDiff) {
				minDiff = diff;
				bestWeight = i;
			}
		}
	}

	//printf("bestWeight=%d\n", bestWeight);

	for (int i = bestWeight; i > 0;) {
		int weight = prev[i];

		//printf("weight %d on first plane, total=%d\n", weight, i);

		for (int j = 0; j < N; j++) {
			if (!w1[j] && w[j] == weight) {
				w1[j] = true;
				break;
			}
		}

		i -= weight;
	}

	bool w1Print, w2Print;
	w1Print = w2Print = false;

	for (int i = 0; i < N; i++) {
		if (w1[i]) {
			printf("%d ", i+1);
			w1Print = true;
		}
	}

	if (!w1Print) {
		printf("0");
	}

	printf("\n");

	for (int i = 0; i < N; i++) {
		if (!w1[i]) {
			printf("%d ", i+1);
			w2Print = true;
		}
	}

	if (!w2Print) {
		printf("0");
	}

	printf("\n");


	return 0;
}