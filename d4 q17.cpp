#include <stdio.h>

void reverseKeys(int keys[], int size) {
    printf("Reversed Keys: ");
    for (int i = size - 1; i >= 0; i--) {
        printf("K%d ", keys[i]);
    }
    printf("\n");
}

int main() {
    int keys[16];
    for (int i = 0; i < 16; i++) {
        keys[i] = i + 1;
    }

    printf("Original Keys: ");
    for (int i = 0; i < 16; i++) {
        printf("K%d ", keys[i]);
    }
    printf("\n");

    reverseKeys(keys, 16);
    return 0;
}

