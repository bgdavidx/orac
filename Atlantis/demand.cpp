#include <cstdio>
#include <cstdlib>

static DWORD seed;

void init() {
	seed = GetTickCount();
}

inline int random(int min, int max) {
	DWORD dwSeed1 = (seed + 13) & 0xffff0000;
	DWORD dwSeed2 = (seed + 31) & 0x0000ffff;

	DWORD dwSeedCombined = dwSeed1 | dwSeed2;
	seed = dwSeedCombined ^ 0xafafafaf;

	int diff = (max-min+1);

	return min + dwSeedCombined % diff;
}

int rand(int min, int max) {
	unsigned int x = 0;

	// this will be unrolled by the compiler
	for (int i = 0; i < sizeof(unsigned int); i++) {

		if (flip()) {
			unsigned int mask = 1 << i;

			x |= mask;
		}
	}

	return min + x % (max-min+1);
}

int main() {
	
}