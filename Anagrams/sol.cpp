#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

const int MAX_WORD_LEN = 30;
const int MAX_WORDS = 650;
const int MAX_N = 200000;
const int MAX_LINE_LEN = 80;

char words[MAX_WORDS+1][MAX_WORD_LEN+1];
char sortedWords[MAX_WORDS+1][MAX_WORD_LEN+1];
int hashes[MAX_WORDS+1], lens[MAX_WORDS+1], numWords;

int hash(char *str, int len) {
	int ret = 13;
	for (int i = 0; i < len; i++) {
		ret += (str[i]);
	}
	return ret;
}

int main() {
	freopen("words.txt", "r", stdin);

	for (int i = 0; ; i++) {
		scanf("%s", words[i]);

		if (words[i][0] == '#') {
			numWords = i;
			break;
		}

		strcpy(sortedWords[i], words[i]);
		int len = strlen(sortedWords[i]);
		std::sort(sortedWords[i], sortedWords[i]+len);

		hashes[i] = hash(sortedWords[i], len);
		lens[i] = len;
	}

	freopen("anagin.txt", "r", stdin);


#ifndef __APPLE__
	freopen("anagout.txt", "w", stdout);
#endif

	for (int i = 0; 1; i++) {
		char line[MAX_LINE_LEN+5];
		char sortedLine[MAX_LINE_LEN+5];
		//gets(line);
		scanf("%81[^\n]%*c", line);
		//printf("LINE READ=%s\n", line);
		int lineLen = strlen(line);
		/*if (line[lineLen-1] == '\n') {
			line[lineLen-1] = '\0';
		}*/

		if (line[0] == '#') {
			break;
		} else {
			int pos = 0;
			for (int j = 0; j < lineLen; j++) {
				char ch = line[j];
				if (ch >= 'a' && ch <= 'z') {
					sortedLine[pos++] = ch;
				} else if (ch >= 'A' && ch <= 'Z') {
					ch -= 'A';
					ch += 'a';
					sortedLine[pos++] = ch;
				}
			}

			sortedLine[pos] = 0;

			//printf("%s %s\n", line, sortedLine);

			std::sort(sortedLine, sortedLine+pos);
			int hashCode = hash(sortedLine, pos);
			bool found = false;

			for (int x = 0; x < numWords; x++) {
				if (lens[x] == pos && hashes[x] == hashCode) {
					if (strcmp(sortedLine, sortedWords[x]) == 0) {
						printf("%s ", words[x]);
						found = true;
					}
					/*for (int y = 0; y < pos; y++) {
						if (y==pos-1) {
							printf("%s ", words[x]);
							found = true;
							break;
						} else if (sortedWords[x][y] != sortedLine[y]) {
							break;
						}
					}*/
				}
			}

			if (!found) {
				printf("No anagram found\n");
			} else {
				printf("\n");
			}

		}
	}

	return 0;
}