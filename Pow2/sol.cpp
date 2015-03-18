#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>

const int MAX_POWER = 10000;

std::vector<char> digits;
char search[205];
int searchLen;
int power = 0;

int main() {
	freopen("pow2in.txt", "r", stdin);
#ifndef __APPLE__
	freopen("pow2out.txt", "w", stdout);
#endif

	scanf("%s", search);

	searchLen = strlen(search);
	for (int i = 0; i < searchLen; i++) {
		search[i] -= '0';
	}

	if (searchLen == 1 && search[0] == 1) {
		printf("0\n");
		return 0;
	}

	/*for (int i = 0; i < searchLen; i++) {
		printf("%d", search[i]);
	}
	printf("\n");*/

	digits.push_back(1);

	while (power < MAX_POWER-1) {
		char carry = 0;

		for (int k = digits.size() - 1; k >= 0; k--) {
			char db = (digits[k]<<1)+carry;
			if (db >= 10) {
				char dig = db % 10;
				carry = (db)/10;
				digits[k] = dig;
			} else {
				digits[k] = db;
				carry = 0;
			}
		}

		if (carry > 0) {
			digits.insert(digits.begin(), carry);
		}

		/*printf("2^%d=", power+1);
		for (int i = 0; i < digits.size(); i++) {
			printf("%d", digits[i]);
		}
		printf("\n");*/

		if (digits.size() >= searchLen) {
			for (int i = 0; i <= digits.size()-searchLen; i++) {
				for (int j = 0; j < searchLen; j++) {
					if (digits[i+j] == search[j]) {
						if (j == searchLen-1) {
							printf("%d\n", power+1);
							return 0;
						}
					} else {
						break;
					}
				}
			}
		}

		power++;
	}

	printf("No solution found\n");
	return 0;
}