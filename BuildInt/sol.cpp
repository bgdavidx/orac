#include <cstdio>
#include <cstdlib>
#include <cstring>

enum { ADD = 0, MULT = 1 };

const int MAX_N = 2001;
const int MAX_LEN = 41;

typedef struct Answer {
	char word[MAX_LEN];
	char len;

	void set(int n) {
		sprintf(word, "%d", n);
		len = strlen(word);
	}

	bool valid() {
		return len > 0;
	}

	bool better(int x) {
		return len == 0 || x < len;
	}

} *pAnswer;

Answer answers[MAX_N][2];

void build();

const char *f(int);

int main() {
	freopen("buildin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("buildout.txt", "w", stdout);
#endif

	build();

	while (true) {
		int n;
		scanf("%d", &n);

		if (!n) {
			break;
		}

		printf("%d=%s\n", n, f(n));
	}

	return 0;
}


// magic below











void build() {
	static const int def[4] = {1, 11, 111, 1111};
	static const int lens[2][2] = {
		{ 5, 3 },
		{ 3, 1 }
	};
	static const char *fmt[2][2] = {
		{ "(%s)*(%s)", "(%s)*%s" },
		{ "%s*(%s)", "%s*%s" }
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= 1; j++) {
			answers[def[i]][j].set(def[i]);
		}
	}


	for (int i = 2; i < MAX_N; i++) {
		for (int j = 1; j < i; j++) {

			if (j <= MAX_N/2) {
				if (j > 1 && i%j == 0) {
					int k = i/j;

					for (int x = 0; x <= 1; x++) {
						for (int y = 0; y <= 1; y++) {
							if (answers[j][x].valid() && answers[k][y].valid()) {
								int newLen = answers[j][x].len + answers[k][y].len + lens[x][y];
								if (answers[i][MULT].better(newLen)) {
									sprintf(answers[i][MULT].word, fmt[x][y], answers[j][x].word, answers[k][y].word);
									answers[i][MULT].len = newLen;
								}
							}
						}
					}
				}
			}

			int k = i - j;

			for (int x = 0; x <= 1; x++) {
				for (int y = 0; y <= 1; y++) {
					if (answers[j][x].valid() && answers[k][y].valid()) {
						int newLen = answers[j][x].len + answers[k][y].len + 1;

						if (answers[i][ADD].better(newLen)) {
							sprintf(answers[i][ADD].word, "%s+%s", answers[j][x].word, answers[k][y].word);
							answers[i][ADD].len = newLen;
						}
					}
				}
			}

		}
	}
}

const char *f(int n) {
	int lA = answers[n][ADD].len;
	int lM = answers[n][MULT].len;

	if ((answers[n][ADD].valid() && lA < lM) || !answers[n][MULT].valid()) {
		return answers[n][ADD].word;
	}

	return answers[n][MULT].word;
}
