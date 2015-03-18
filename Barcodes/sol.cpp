#include <cstdio>
#include <cstdlib>
#include <vector>

int W;
char barcode[5][101];

enum DecodeState {
	UNKNOWN = 0,
	BLACK,
	WHITE
};

DecodeState decoded[101];
std::vector<int> vec;

int main() {
	freopen("barin.txt", "r", stdin);
	//freopen("barout.txt", "w", stdout);

	scanf("%d", &W);

	for (int i = 0; i < 5; i++) {
		scanf("%s", barcode[i]);
	}

	for (int i = 0; i < W; i++) {
		for (int j = 0; j < 5; j++) {
			char cur = barcode[j][i];
			if (cur == 'B') {
				decoded[i] = BLACK;
				break;
			} else if (cur == '.') {
				decoded[i] = WHITE;
				break;
			}
		}
	}

	for (int i = 0; i < W; i++) {
		if (decoded[i] === UNKNOWN) {
			// ?BB is not ambiguous
			// ?WB is ambiguous - could be WWB or BWB
			// B?B is not ambiguous
			// B?W is ambiguous

			if (i == 0) {
				
			}
		}
	}

	int lastColor = -1;

	for (int i = 0; i < W; i++) {
		if (lastColor == decoded[i]) {
			vec.push_back(1);
		} else if (decoded[i] == UNKNOWN) {
			vec.push_back(-1);
		} else if (lastColor != -1) {
			vec.push_back(0);
		}

		lastColor = decoded[i];
	}

	for (int i = 0; i < vec.size(); i++) {
		printf("%d ", vec[i]);
	}

	printf("\n");

	return 0;
}