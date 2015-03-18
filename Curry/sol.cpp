#include <cstdio>
#include <cstdlib>
#include <algorithm>

int crv[3];
int riceWithVegetables, curryWithVegetables, curryWithRice;

#define CurryType 0
#define RiceType 1
#define VegetableType 2

int main() {
	freopen("curryin.txt", "r", stdin);
	freopen("curryout.txt", "w", stdout);

	scanf("%d %d %d", &crv[0], &crv[1], &crv[2]);

	// pick the 2 largest ones and sub

	while (true) {
		int largestIndex = -1;
		int secondLargestIndex = -1;
		int largestVal = -1;
		int secondLargestVal = -1;

		for (int i = 0; i < 3; i++) {
			if (crv[i] > largestVal && crv[i] != 0) {
				largestIndex = i;
				largestVal = crv[i];
			}
		}

		for (int i = 0; i < 3; i++) {
			if (crv[i] > secondLargestVal && crv[i] != 0 && i != largestIndex) {
				secondLargestIndex = i;
				secondLargestVal = crv[i];
			}
		}

		if (largestIndex == -1 || secondLargestIndex == -1) {
			break;
		}

		crv[largestIndex] -= secondLargestVal;
		crv[secondLargestIndex] -= secondLargestVal;

		if (largestIndex == RiceType && secondLargestIndex == VegetableType ||
			largestIndex == VegetableType && secondLargestIndex == RiceType) {
			riceWithVegetables += secondLargestVal;
		} else if (largestIndex == CurryType && secondLargestIndex == VegetableType ||
			largestIndex == VegetableType && secondLargestIndex == CurryType) {
			curryWithVegetables += secondLargestVal;
		} else {
			curryWithRice += secondLargestVal;
		}

		printf("%d %d %d\n\n", crv[0], crv[1], crv[2]);
	}

	printf("%d %d %d\n", riceWithVegetables, curryWithVegetables, curryWithRice);

	return 0;
}