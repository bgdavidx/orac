#include <cstdio>
#include <cstdlib>

#define MAX_N 61
#define MAX_W 61000

int n;
int luggageWeights[MAX_N];
bool includedA[MAX_N][MAX_N] = { 0 };
bool subset[MAX_W][MAX_N] = { 0 };

int main() {
	freopen("balin.txt", "r", stdin);
	freopen("balout.txt", "w", stdout);

	scanf("%d", &n);

	int totalWeight = 0;

	for (int i = 0; i < n; i++) {
		scanf("%d", &luggageWeights[i]);
		totalWeight += luggageWeights[i];
	}

	// we want to find a subset of luggageWeights that is closest to perfectWeight
	// such that we have MIN(ABS(perfectWeight-subsetWeight))

	// all subsets summing to zero are true
	for (int i = 0; i <= n; i++) {
		subset[0][i] = true;
	}

	// it is impossible for a subset that contains numbers to sum to zero
	for (int i = 1; i <= totalWeight; i++) {
		subset[i][0] = false;
	}

	// build the truth table for possibility of summing
	for (int i = 1; i <= totalWeight; i++) {
		for (int j = 0; j < n; j++) {
			subset[i][j+1] = subset[i][j];
			if (i >= luggageWeights[j]) {
				// subset[i][j] is true if luggageWeights can sum to i
				/*if (subset[i-luggageWeights[j]][j]) {
					printf("%d a\n", j);
				}*/
				subset[i][j+1] = subset[i][j] || subset[i-luggageWeights[j]][j];
			}
		}
	}

	int min = 9999999;

	int closestNum;
	int firstItem;

	for (int i = 1; i <= totalWeight; i++) {
		for (int j = 1; j <= n; j++) {
			// if a subset with weight i exists
			if (subset[i][j]) {
				int possibleMin = abs(totalWeight - 2 * i);
				if (possibleMin < min) {
					min = possibleMin;
					closestNum = i;
					firstItem = j;
				}
			}
		}
	}


	printf("closestNum=%d\n\n", closestNum);

	//printf("%d %d\n", backtrackI, backtrackJ);
	//printf("Diff between two sub sets will be : %d\n", min);
	/*for (int i = 1; i <= n; i++) {
		if (subset[closestNum][i]) {
			printf("%d ", i);
		}
	}

	printf("\n");

	for (int i = 1; i <= n; i++) {
		if (!subset[closestNum][i]) {
			printf("%d ", i);
		}
	}*/

	/*int whatNum = closestNum;
	int itemNum = firstItem;

	while (whatNum > 0) {
		printf("%d ", itemNum);
		whatNum -= luggageWeights[itemNum];
	}*/

	for (int i = n; i > 0; i--) {
		for (int j = 1; j <= totalWeight; j++) {
			if (subset[j][firstItem]) {
				printf("%d ", i);
				break;
			}
		}
	}

	printf("\n");


	return 0;
}