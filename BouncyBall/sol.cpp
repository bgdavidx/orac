#include <cstdio>
#include <cstdlib>

const static int MAX_N = 120;

int path[MAX_N] = { 0 }, pathLen = 0;
int N, acc, K;

int main() {
	freopen("ballin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("ballout.txt", "w", stdout);
#endif

	scanf("%d %d %d", &N, &acc, &K);

	int base = 0;

	// create first case
	{
		int t = acc;
		int total = t;
		base = t;
		for (;;) {
			path[pathLen++] = t;
			t += acc;

			if (total + t + t >= N) {
				//printf("total=%d\n", total);
				int last = N - total;
				path[pathLen++] = last;
				break;
			}

			total += t;
		}
	}

	for (int i = 0; i < K-1; i++) {
		if (pathLen == 2) {
			//printf("should fix it here\n");

			base += acc;
			int t = base;
			int total = base;
			pathLen = 0;
			for (;;) {
				path[pathLen++] = t;
				t += acc;

				if (total + t + t >= N) {
					//printf("total=%d\n", total);
					int last = N - total;
					path[pathLen++] = last;
					break;
				}

				total += t;
			}
		} else {
			int possibleLast = path[pathLen-1] - acc;
			int possibleSecondLast = path[pathLen-2] + acc;

			if (possibleLast > possibleSecondLast) {
				path[pathLen-1] = possibleLast;
				path[pathLen-2] = possibleSecondLast;
			} else {
				path[pathLen-2] += path[pathLen-1];
				pathLen--;
			}
		}

		//printf("perm %d: ", i+1);

		/*for (int i = 0; i < pathLen; i++) {
			printf("%d ", path[i]);
		}

		printf("\n");*/
	}

	for (int i = 0; i < pathLen; i++) {
		printf("%d ", path[i]);
	}

	printf("\n");

	return 0;
}