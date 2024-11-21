#include <stdio.h>

void generateSubkeys(unsigned long initialKey) {
    printf("Initial Key: %lx\n", initialKey);

    for (int i = 1; i <= 16; i++) {
        unsigned long leftHalf = (initialKey >> 28) & 0xFFFFFFF;
        unsigned long rightHalf = initialKey & 0xFFFFFFF;

        // Left shift each half
        leftHalf = (leftHalf << i) | (leftHalf >> (28 - i));
        rightHalf = (rightHalf << i) | (rightHalf >> (28 - i));

        // Combine 24 bits from each half
        unsigned long subkey = ((leftHalf & 0xFFFFFF) << 24) | (rightHalf & 0xFFFFFF);
        printf("Subkey %d: %lx\n", i, subkey);
    }
}

int main() {
    unsigned long initialKey = 0x123456789ABCDE;
    generateSubkeys(initialKey);
    return 0;
}

