#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>

#define MakePoint(X, Y) (std::make_pair((X), (Y)))

typedef std::pair<int,int> Point;
typedef const unsigned int CUNT;

struct Step {
	bool placed[5];
	int count;

	Step() : count(0) {
		memset(placed, 0, sizeof(placed));
	}
};

// C = y, R = x
CUNT MAX_C = 60;
CUNT MAX_R = 60;

static const char ALPHABET[] = "&ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int *stuff = 0;
int board[MAX_R][MAX_C] = {0};
int solution[MAX_R][MAX_C] = {0};
int rows, cols;
int needToSolve;
const int DIR[4][2] = {
	{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }
};
const int DIR_ALL[8][2] = {
	{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 },
	{ -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 }
};

bool solve(int r, int c, Step &step, int solvedCount) {

	//printf("Solve %d %d %d %d\n", r, c, solvedCount, step.count);

	int wtf = board[r][c];

	step.placed[wtf] = true;
	step.count++;
	solution[r][c] = solvedCount;

	/*if (step.count == 5) {
		printf("Solved step %d\n", solvedCount+1);
	}*/

	if (step.count == 5 && solvedCount*5 >= needToSolve) {
		//printf("Solved all\n");
		return true;
	}

	if (step.count < 5) {
		for (int i = 0; i < 4; i++) {
			int nextRow = r+DIR[i][0];
			int nextCol = c+DIR[i][1];

			if (nextRow >= 0 && nextCol >= 0 && nextRow < rows && 
				nextCol < cols && solution[nextRow][nextCol] == 0) {
				if (!step.placed[board[nextRow][nextCol]] && 
					solve(nextRow, nextCol, step, solvedCount)) {
					return true;
				}
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			int nextRow = r+DIR_ALL[i][0];
			int nextCol = c+DIR_ALL[i][1];

			if (nextRow >= 0 && nextCol >= 0 && nextRow < rows && 
				nextCol < cols && solution[nextRow][nextCol] == 0) {
				Step nextStep;
				//printf("solving next step at %d %d\n", nextRow, nextCol);
				if (solve(nextRow, nextCol, nextStep, solvedCount+1)) {
					return true;
				}
			}
		}
	}

	step.placed[wtf] = false;
	step.count--;
	solution[r][c] = 0;

	return false;
}

int main() {
	freopen("pentin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("pentout.txt", "w", stdout);
#endif

	scanf("%d %d", &rows, &cols);
	needToSolve = rows * cols;

	for (int i = 0; i < rows; i++) {
		char s[MAX_C];
		scanf("%s", s);
		for (int j = 0; j < cols; j++) {
			board[i][j] = s[j] - '1';
			//printf("%d", board[i][j]);
		}
		//printf("\n");
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			Step step;
			if (solve(i, j, step, 1)) {
				goto end;
			}
		}
	}

	//printf("Failed to find solution\n");

	*((int*)stuff) = 12;
		
end:
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			putchar(ALPHABET[solution[i][j]]);
		}
		putchar('\n');
	}

	return 0;
}