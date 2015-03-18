#include <cstdio>
#include <cstdlib>
#include <utility>
#include <queue>
#include <stack>

const int MAX_X = 100;
const int MAX_Y = 100;

enum SquareState { LAND = 0, WATER = 1 };


typedef std::pair<int,int> Point;

#define MakePoint(X, Y) (std::make_pair((X),(Y)))

int map[MAX_X][MAX_Y], width, height;
bool seen[MAX_X][MAX_Y];
int initialHeight, finalHeight;
SquareState states[MAX_X][MAX_Y];

const int floodDir[8][2] = 
{
	{ -1, -1 },
	{ 0, -1 },
	{ 1, -1},
	{ -1, 0},
	{ 1, 0},
	{-1, 1},
	{0, 1},
	{1, 1}
};

int main() {
	freopen("atlanin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("atlanout.txt", "w", stdout);
#endif

	scanf("%d %d", &initialHeight, &finalHeight);
	scanf("%d %d", &width, &height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			scanf("%d", &map[i][j]);
			states[i][j] = LAND;
		}
	}

	// run first flood

	{
		std::queue<Point> q;

		// fill horizontally
		for (int i = 0; i < width; i++) {
			q.push(MakePoint(i, 0));
			q.push(MakePoint(i, height-1));
			seen[i][0] = true;
			seen[i][height-1] = true;
		}

		for (int i = 0; i < height; i++) {
			q.push(MakePoint(0, i));
			q.push(MakePoint(width-1, i));
			seen[0][i] = true;
			seen[width-1][i] = true;
		}

		while (!q.empty()) {
			Point pt = q.front();
			q.pop();

			int px = pt.first;
			int py = pt.second;

			int height = map[px][py];

			if (height > initialHeight) {
				continue;
			} else {
				// flood all adjacent squares
				states[px][py] = WATER;
				for (int i = 0; i < 8; i++) {
					int nx = px+floodDir[i][0];
					int ny = py+floodDir[i][1];

					if (nx < 0 || ny < 0 || nx >= width || ny >= height || seen[nx][ny]) {
						continue;
					}

					seen[nx][ny] = true;
					q.push(MakePoint(nx, ny));
				}
			}
		}
	}

#ifdef __APPLE__
	{
		// testing
		int tot = 0;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (states[i][j] == LAND) {
					tot++;
				}
				printf("%d ", states[i][j]);
			}
			printf("\n");
		}

		printf("\nAfter flooding we have %d land squares\n", tot);
	}
#endif

	{
		std::queue<Point> q;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				seen[i][j] = false;
			}
		}

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (states[i][j] == LAND && map[i][j] > initialHeight) {
					//q.push(MakePoint(i, j));
					//seen[i][j] = true;

					for (int i = 0; i < 8; i++) {
						int nx = i+floodDir[i][0];
						int ny = j+floodDir[i][1];

						if (nx < 0 || ny < 0 || nx >= width || ny >= height || seen[nx][ny]) {
							continue;
						}

						seen[nx][ny] = true;
						q.push(MakePoint(nx, ny));
					}
				}
			}
		}
		

		while (!q.empty()) {
			Point pt = q.front();
			q.pop();

			int px = pt.first;
			int py = pt.second;

			int height = map[px][py];

			if (height < finalHeight) {
				states[px][py] = WATER;
				continue;
			} else {
				states[px][py] = LAND;
				for (int i = 0; i < 8; i++) {
					int nx = px+floodDir[i][0];
					int ny = py+floodDir[i][1];

					if (nx < 0 || ny < 0 || nx >= width || ny >= height || seen[nx][ny] ||
							(map[nx][ny] < map[px][py] && states[nx][ny] == WATER)) {
						continue;
					}

					seen[nx][ny] = true;
					q.push(MakePoint(nx, ny));
				}
			}
		}
	}

#ifdef __APPLE__
	{
		// testing
		int tot = 0;
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				if (states[i][j] == WATER) {
					tot++;
				}
				printf("%d ", states[i][j]);
			}
			printf("\n");
		}

		printf("\nAfter subsiding we have %d water squares\n", tot);
	}
#else
	int tot = 0;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (states[i][j] == WATER) {
				tot++;
			}
		}
	}

	printf("%d\n", tot);

#endif

	return 0;
}