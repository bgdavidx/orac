#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>

struct Entry {
	char name[21];
	int score;
};

#define MAX_C 35
int S, C;
int count;
struct Entry entries[MAX_C];

int main() {
	freopen("scores.in", "r", stdin);
#ifndef __APPLE__
	freopen("scores.out", "w", stdout);
#endif

	scanf("%d %d", &S, &C);

	count = 0;

	for (int i = 0; i < S; i++) {
		if (count == C) {
			count = 0;
		}

		scanf("%s %d", entries[count].name, &entries[count].score);

		int x = count;

		while (x > 0 && entries[x>>1].score < entries[x].score) {
			Entry e = entries[x>>1];
			entries[x>>1] = entries[x];
			entries[x] = e;
			x = x>>1;
		}

		count++;
	}

	int a = 3;

	while (a--) {
		if (!count) {
			printf("NULL -1\n");
			continue;
		}
		Entry top = entries[0];
		printf("%s %d\n", top.name, top.score);

		entries[0] = entries[count-1];

		int index = 0;

		while (2*index+1 < count) {
			int child = 2*index+1;
			if (child<count-1 && entries[child].score < entries[child+1].score) {
				child++;
			}

			if (entries[child].score > entries[index].score) {
				Entry e = entries[child];
				entries[child] = entries[index];
				entries[index] = e;
				index = child;
			} else {
				break;
			}
		}

		count--;
	}
}