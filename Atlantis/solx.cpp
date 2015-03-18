#include <cstdio>
#include <cstdlib>
#include <utility>
#include <queue>
#include <stack>

const int MAX_R = 100;
const int MAX_C = 100;

enum SquareState { LAND = 0, WATER = 1 };


typedef std::pair<int,int> Point;

#define MakePoint(X, Y) (std::make_pair((X),(Y)))

int map[MAX_R][MAX_C], rows, cols;
bool seen[MAX_R][MAX_C];
int initialHeight, finalHeight;
SquareState states[MAX_R][MAX_C];

int main() {
	freopen("atlanin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("atlanout.txt", "w", stdout);
#endif

	scanf("%d %d", &initialHeight, &finalHeight);
	scanf("%d %d", &rows, &cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &map[i][j]);
			states[i][j] = LAND;
		}
	}

	const int floodDir[8][2] = {
		{ -1, -1 },
		{ 0, -1 },
		{ 1, -1},
		{ -1, 0},
		{ 1, 0},
		{-1, 1},
		{0, 1},
		{1, 1}
	};

	// RUN BFS

	memset(seen, sizeof(seen), 0);

	{
		std::queue<Point> bfs;
		for (int i = 0; i < cols; i++) {
			bfs.push(MakePoint(0, i));
			bfs.push(MakePoint(rows-1, i));
			seen[0][i] = true;
			seen[rows-1][i] = true;
		}

		for (int i = 1; i < rows-1; i++) {
			bfs.push(MakePoint(i, 0));
			bfs.push(MakePoint(i, cols-1));
			seen[i][0] = true;
			seen[i][cols-1] = true;
		}

		while (!bfs.empty()) {
			Point pt = bfs.front();
			bfs.pop();

			int x = pt.first;
			int y = pt.second;

			//if (seen[x][y]) continue;

			//printf("Searching %d %d\n", x, y);

			if (map[x][y] > initialHeight) {
				//printf("%d %d %d is above water\n", x, y, map[x][y]);
				states[x][y] = LAND;
				continue;
			} else {
				//printf("%d %d is flooded\n", x, y);
				states[x][y] = WATER;

				for (int i = 0; i < 8; i++) {
					int nx = x+floodDir[i][0];
					int ny = y+floodDir[i][1];

					if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || seen[nx][ny]) {
						continue;
					}

					seen[nx][ny] = true;
					bfs.push(MakePoint(nx, ny));
				}
			}
		}
	}

	int wat = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (states[i][j] == LAND) {
				wat++;
			}
			printf("%d ", states[i][j]);
		}
		printf("\n");
	}

	printf("land=%d\n", wat);

	memset(seen, sizeof(seen), 0);

	{
		std::queue<Point> bfs;
		for (int i = 0; i < cols; i++) {
			bfs.push(MakePoint(0, i));
			bfs.push(MakePoint(rows-1, i));
			seen[0][i] = true;
			seen[rows-1][i] = true;
		}

		for (int i = 1; i < rows-1; i++) {
			bfs.push(MakePoint(i, 0));
			bfs.push(MakePoint(i, cols-1));
			seen[i][0] = true;
			seen[i][cols-1] = true;
		}

		while (!bfs.empty()) {
			Point pt = bfs.front();
			bfs.pop();

			int x = pt.first;
			int y = pt.second;

			//if (seen[x][y]) continue;

			//printf("Searching %d %d\n", x, y);

			if (map[x][y] < finalHeight) {
				printf("%d %d %d is underwater\n", x, y, map[x][y]);
				states[x][y] = WATER;
				continue;
			} else {
				printf("%d %d is exposed\n", x, y);
				states[x][y] = LAND;

				for (int i = 0; i < 8; i++) {
					int nx = x+floodDir[i][0];
					int ny = y+floodDir[i][1];

					if (nx < 0 || ny < 0 || nx >= rows || ny >= cols || seen[nx][ny]) {
						continue;
					}

					seen[nx][ny] = true;
					bfs.push(MakePoint(nx, ny));
				}
			}
		}
	}

	wat = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (states[i][j] == LAND) {
				wat++;
			}
			printf("%d ", states[i][j]);
		}
		printf("\n");
	}

	printf("land=%d\n", wat);

	return 0;
}