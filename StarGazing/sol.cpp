#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <algorithm>

const int MAX_N = 2005;
const int MAX_Y = 1000001;

std::vector<int> xList[MAX_Y];
int N;

int main() {
#ifdef __APPLE__
	freopen("starin.txt", "r", stdin);
#endif

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		xList[y].push_back(x);
	}

	for (int i = 0; i < MAX_Y; i++) {
		if (xList[i].size() > 0) {
			std::sort(xList[i].begin(), xList[i].end());
		}
	}

	int ans = 0;

	for (int i = MAX_Y - 1; i > 0; i--) {
		if (xList[i].size() > 1) {
			for (int j = 0; j < xList[i].size() - 1; i++) {
				for (int k = j+1; k < xList[i].size(); k++) {
					int x1 = xList[i][j];
					int x3 = xList[i][k];

					int w = x3 - x1;

					if (w >= 3) {
						int searchStart = i - w - 1;
						if (searchStart >= 0) {
							for (; searchStart >= 0; searchStart--) {
								if (xList[searchStart].size() > 0) {
									std::vector<int>::iterator left = std::upper_bound(xList[i].begin(), xList[i].end(), x1);

									if (left != xList[searchStart].end()) {
										std::vector<int>::iterator right = std::lower_bound(xList[i].begin(), xList[i].end(), x3);

										if (right != xList[searchStart].end()) {
											for (; left != right; left++) {
												int x2 = *left;
												int y2 = searchStart;

												int size = y2-i + w;

												if (size > ans) {
													ans = size;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	printf("%d\n", ans);

	return 0;
}