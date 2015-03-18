#include <cstdio>
#include <cstdlib>

int N;
char students[201];

int main() {
	freopen("serious.in", "r", stdin);
	freopen("serious.out", "w", stdout);

	scanf("%d", &N);
	scanf("%s", students);

	int ans = 0;
	int whereAmI = 0;

	for (int i = 0; i < N; i++) {
		char student = students[i];

		if (student >= 'A' && student <= 'Z') {
			// hardworker
			while (whereAmI%4 != 0) {
				whereAmI++;
				ans++;
			}
		}

		whereAmI++;
	}

	printf("%d\n", ans);

	return 0;
}