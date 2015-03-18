#include <cstdio>
#include <cstdlib>
#include <queue>

std::priority_queue<int> pq;
int N;

int main() {
	freopen("packagein.txt", "r", stdin);
#ifndef __APPLE__
	freopen("packageout.txt", "w", stdout);
#endif

	scanf("%d", &N);

	int x;

	for (int i = 0; i < N; i++) {
		scanf("%d", &x);
		if (x) {
			pq.push(x);
		} else {
			scanf("%d", &x);
			for (int j = 0; j < x; j++) {
				printf("%d ", pq.top());
				pq.pop();
			}
			printf("\n");
		}
	}

	return 0;
}