#include <cstdio>
#include <cstdlib>

int w,h, ans = 0;
char buf[100];

int main() {
	freopen("cartin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("cartout.txt", "w", stdout);
#endif
	scanf("%d %d", &w, &h);
	for (int i = 0; i < h; i++) {
		scanf("%s", &buf);
		int start = 0, end = 0;
		bool found1 = false, found2 = false;
		for (start = 0; start < w; start++) {
			if (buf[start]=='#') {
				found1 = true;
				break;
			}
		}
		for (end = w-1; end >= 0; end--) {
			if (buf[end] == '#') {
				found2 = true;
				break;
			}
		}

		if (found1&found2)
			ans += end-start+1;
	}
	printf("%d\n", ans);

	return 0;
}