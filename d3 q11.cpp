#include <stdio.h>
#include <math.h>

int main() {
    unsigned long long factorial = 1;
    for (int i = 2; i <= 25; i++) {
        factorial *= i;
    }
    printf("Approximate unique Playfair cipher keys (in power of 2): ~2^%.0f\n", log2(factorial));
    return 0;
}

