#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <iostream>
#include <vector>

#define MAX_N 1000

int N;
std::vector<std::string> out(MAX_N);
std::map<std::string, int> m1;

int main() {
	freopen("camin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("camout.txt", "w", stdout);
#endif

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		char plate[10];
		scanf("%s", plate);

		m1[plate] = i;
	}


	/*
	REDCAR
	L0LL1P0P
	UQ9396
	109DLY
	B1LKENT

	B1LKENT
	UQ9396
	REDCAR
	L0LL1P0P
	109DLY


	UQ9396
	REDCAR
	L0LL1P0P
	109DLY
	B1LKENT

	
	
	REDCAR
	L0LL1P0P
	UQ9396
	109DLY
	B1LKENT

	109DLY
	SSH2ANU
	VOLVO76
	REDCAR

	REDCAR
	109DLY
	SSH2ANU
	VOLVO76

	*/

	for (int i = 0; i < N; i++) {
		char stuff[10];
		scanf("%s", stuff);
		out[i] = stuff;
		//printf("%s=%d\n", out[i].c_str(), out[i].size());
	}

	/*for (int k = 0; k < out.size(); k++) {
		printf("%s ", out[k].c_str());
	}
	printf("\n");
	return 0;*/

	int ans = 0;

	for (;;) {
		bool inOrder = true;

		// find one that isn't in order
		for (int i = 0; i < out.size(); i++) {
			printf("PROCESSING: %s\n", out[i].c_str());
			if (m1[out[i]] != i) {
				ans++;
				inOrder = false;
				std::string stuff = out[i];
				for (int k = 0; k < out.size(); k++) {
					printf("%s ", out[k].c_str());
				}
				printf("\n");
				out.erase(out.begin() + i);
								
				printf("\n");
				printf("insert location=%d\n", m1[stuff]);
				out.insert(out.begin() + m1[out[i]], stuff);

				for (int k = 0; k < out.size(); k++) {
					printf("%s ", out[k].c_str());
				}
				printf("\n");
				if (ans > 2) {
					exit(1);
				}
				break;
			} else {
				printf("%s is in the right place\n", out[i].c_str());
			}
		}

		if (inOrder) {
			break;
		}
	}

	printf("%d\n", ans);

	return 0;
}