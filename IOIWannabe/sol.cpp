#include <cstdio>
#include <cstdlib>

const int MAX_R = 1501;
const int MAX_C = MAX_R;

int building[MAX_R][MAX_C];
int fruitBelow[MAX_R][MAX_C];
int spikesAbove[MAX_R][MAX_C];
int maxes[MAX_R][MAX_C];

int R, C;

int findMax(int i, int j) {

	int cur;

	if (val > 0) {
		// fruit
		cur = fruitBelow[i][j] + spikesAbove[i][j] - building[i][j];
	} else {
		// spike
		cur = fruitBelow[i][j] + spikesAbove[i][j] + building[i][j];
	}

	int downRight = findMax(i+1, j+1);
	
}

int main() {
	freopen("wannabe.in", "r", stdin);
#ifndef __APPLE__
	freopen("wannabe.out", "w", stdout);
#endif

	scanf("%d %d", &R, &C);

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &building[i][j]);
			maxes[i][j] = -1;
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (building[i][j] > 0) {
				// fruit goes up
				fruitBelow[0][j] += building[i][j]
			} else {
				// spikes go down
				spikesAbove[R-1][j] -= building[i][j];
			}
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int k = C - j - 1;

			if (i > 0 && building[i][j] > 0) {
				// fruit
				fruitBelow[i][j] = fruitBelow[i-1][j] - building[i][j];
			}

			if (k < C - 1 && building[i][k] < 0) {
				// spikes
				spikesAbove[i][k] = spikesAbove[k+1][j] + building[i][j];
			}
		}
	}
}