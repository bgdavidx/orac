#include <cstdio>
#include <cstdlib>
#include <vector>

std::vector<int> fl [1001][1001];

int main() {
	freopen("popin.txt", "r", stdin);
	freopen("popout.txt", "w", stdout);

	//printf("hey there\n");

	int id = 1;


	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		if (x == -1 && y == -1) {
			break;
		}

		fl[x/1000][y/1000].push_back(id);

		id++;
	}

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);

		//printf("%d, %d\n", x, y);

		if (x == -1 && y == -1) {
			break;
		}

		std::vector<int> f = fl[x/1000][y/1000];

		if (f.size() == 0) {
			printf("Nobody.\n");
		} else {
			for (int i = 0; i < f.size(); i++) {
				printf("%d ", f[i]);
			}
			printf("\n");
		}
	}

	return 0;
}