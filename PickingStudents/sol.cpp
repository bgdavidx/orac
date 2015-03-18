#include <cstdio>
#include <cstdlib>

const int ZEROS = 100000;

inline int min(int a, int b) {
    return (a<b)? a: b;
}

int ncr(const int n, const int k) {
    int* C = (int*)calloc(k+1, sizeof(int));
    int i, j, res;
 
    C[0] = 1;
 
    for(i = 1; i <= n; i++) {
        for(j = min(i, k); j > 0; j--)
            C[j] = (C[j]%ZEROS + C[j-1]%ZEROS)%ZEROS;
    }
 
    res = C[k];
 
    free(C);
 
    return res%ZEROS;
}

int main() {
    freopen("pick.in", "r", stdin);
#ifndef __APPLE__
    freopen("pick.out", "w", stdout);
#endif
    int N, K;
    scanf("%d %d", &N, &K);
    printf("%d\n", ncr(N, K));
    return 0;
}