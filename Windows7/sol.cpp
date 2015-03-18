#include <cstdio>
#include <cstdlib>

unsigned char computer_states[1000000];
unsigned int minutes, computers;

int main() {
	freopen("win7.in", "r", stdin);
#ifndef __APPLE__
	freopen("win7.out", "w", stdout);
#endif
	scanf("%d %d", &computers, &minutes);
	for (unsigned int x = 0; x < computers; x++) scanf("%d", &computer_states[x]);

	for (unsigned int i = 0; i < minutes; i++) {
		char first = computer_states[0];
		for (int j = 0; j < computers; j++) {
			char state = j == computers - 1 ? first : computer_states[j + 1];
			if (state) {
				computer_states[j] = !computer_states[j];
			}
		}

		for (int i = 0; i < computers; i++) { printf("%d x\n", computer_states[i]); }
			puts("");
	}
	for (int i = 0; i < computers; i++) { printf("%d\n", computer_states[i]); }

		return 0;
}