#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int MAX_N = 12;

int N;
int table[MAX_N];
int seatedNext[MAX_N][2], seatedCount = 0;
int notSeatedNext[MAX_N][2], notSeatedCount = 0;

int main() {
	freopen("arthin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("arthout.txt", "w", stdout);
#endif
	
	scanf("%d", &N);

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		if (x == 0 && y == 0) break;
		seatedNext[seatedCount][0] = x;
		seatedNext[seatedCount++][1] = y;
	}

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		if (x == 0 && y == 0) break;
		notSeatedNext[notSeatedCount][0] = x;
		notSeatedNext[notSeatedCount++][1] = y;
	}

	for (int i = 0; i < N; i++) {
		table[i] = i+1;
	}

	do {
		// check force seated
		bool pass = false;
		for (int i = 0; i < seatedCount; i++) {
			bool ok = false;
			for (int j = 0; j < N; j++) {
				int next = j == N-1? 0 : j+1;
				int a = table[j];
				int b = table[next];

				if ((a == seatedNext[j][0] && b == seatedNext[j][1]) ||
					(a == seatedNext[j][1] && b == seatedNext[j][0])) {
					ok = true;
					break;
				}
			}

			if (!ok) {
				break;
			}

			if (i == seatedCount - 1) {
				pass = true;
			}
 		}

 		if (!pass) {
 			continue;
 		}

 		pass = false;
		for (int i = 0; i < notSeatedCount; i++) {
			bool ok = true;
			for (int j = 0; j < N; j++) {
				int next = j == N-1? 0 : j+1;
				int a = table[j];
				int b = table[next];

				if ((a == notSeatedNext[j][0] && b == notSeatedNext[j][1]) ||
					(a == notSeatedNext[j][1] && b == notSeatedNext[j][0])) {
					ok = false;
					break;
				}
			}

			if (!ok) {
				break;
			}

			if (i == notSeatedCount - 1) {
				pass = true;
			}
 		}

 		if (!pass) {
 			continue;
 		}

 		// we found one that works!
 		for (int i = 0; i < N; i++) {
 			printf("%d ", table[i]);
 		}

 		printf("\n");

 		return 0;
	} while (std::next_permutation(table, table+N));

	printf("Meeting cancelled.\n");

	return 0;
}

#if 0
int N;
int table[MAX_N];
int seatedNext[MAX_N][2], seatedCount = 0;
int notSeatedNext[MAX_N][2], notSeatedCount = 0;
int index[MAX_N];

void swap(int k1, int k2, int m1, int m2) {

}

bool seatThemHelper(int seatN, bool notSeat) {
	if (notSeat) {
		// satisfy not seating requirement
		return true;
	} else {
		// satisfy seating requirement
		/*for (int i = 0; i < seatedCount; i++) {
			int a1 = seatedNext[i][0];
			int a2 = seatedNext[i][1];

			// try placing them here
			for (int j = 0; j < N; j++) {

			}
		}*/
		for (int i = 0; i < N; i++) {
			// try seating them here'
			int next = i == N-1 ? 0 : i+1;
			int ta = table[i];
			int tb = table[next];
			int a1 = seatedNext[seatN][0];
			int a2 = seatedNext[seatN][1];
			table[i] = a1;
			table[next] = a2;

			if (seatN == seatedCount - 1) {
				if (seatThemHelper(0, true)) {
					return true;
				}

				table[i] = a2;
				table[next] = a1;

				if (seatThemHelper(0, true)) {
					return true;
				}

				table[i] = ta;
				table[next] = tb;
			} else {
				if (seatThemHelper(seatN+1, false)) {
					return true;
				}

				table[i] = a2;
				table[next] = a1;

				if (seatThemHelper(seatN+1, false)) {
					return true;
				}

				table[i] = ta;
				table[next] = tb;
			}
		}

		return false;
	}

	return false;
}

int main() {
	freopen("arthin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("arthout.txt", "w", stdout);
#endif
	
	scanf("%d", &N);

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		if (x == 0 && y == 0) break;
		seatedNext[seatedCount][0] = x;
		seatedNext[seatedCount++][1] = y;
	}

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		if (x == 0 && y == 0) break;
		notSeatedNext[notSeatedCount][0] = x;
		notSeatedNext[notSeatedCount++][1] = y;
	}

	for (int i = 0; i < N; i++) {
		table[i] = i+1;
		index[i] = i+1;
	}

	if (seatThemHelper(0, false)) {
		for (int i = 0; i < N; i++) {
			printf("%d ", table[i]);
		}
		printf("\n");
	} else {
		printf("Meeting cancelled.\n");
	}

	return 0;
}
#endif