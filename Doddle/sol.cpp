#include <cstdio>
#include <cctype>
#include <algorithm>

#define MAX_N 1000005

int16_t data[MAX_N];
int32_t N;

inline int16_t abs(int16_t x) { return x < 0 ? -x : x; }

void siftDown(int32_t, int32_t);

int main() {
	freopen("sortin.txt", "r", stdin);
#ifndef __APPLE__
	freopen("sortout.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%hd", &data[i]);
	}

	{
		for (int32_t i = N/2; i >= 0; i--) {
			siftDown(i, N);
		}
	}

	int32_t count = N-1;
	while (count > 0) {
		int16_t t = data[count];
		data[count] = data[0];
		data[0] = t;
		siftDown(0, count);
		count--;
	}

	for (int i = 0; i < N; i++) {
		printf("%hd\n", data[i]);
	}
	

	return 0;
}

void siftDown(int32_t x, int32_t size) {
    while ((x * 2 + 1) < size) {
    	int32_t child = 2 * x + 1;
    	if (child < size-1 && abs(data[child]) < abs(data[child+1])) {
    		child++;
    	}

    	if (abs(data[child]) > abs(data[x])) {
    		int16_t t = data[child];
    		data[child] = data[x];
    		data[x] = t;
    		x = child;
    	} else {
    		return;
    	}
    }


}