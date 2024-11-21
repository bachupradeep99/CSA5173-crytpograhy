#include <stdio.h>
#include <string.h>

void simulateErrorPropagation(char plaintext[], int blockSize) {
    printf("ECB Mode:\n");
    for (int i = 0; i < strlen(plaintext); i += blockSize) {
        printf("Block %d: ", i / blockSize);
        for (int j = 0; j < blockSize; j++) {
            printf("%c", plaintext[i + j]);
        }
        printf("\n");
    }

    printf("\nCBC Mode (error in block 1):\n");
    printf("Block 1 corrupted\n");
    for (int i = 0; i < strlen(plaintext); i += blockSize) {
        printf("Block %d: CORRUPTED\n", i / blockSize);
    }
}

int main() {
    char plaintext[] = "ERRORPROPAGATIONTEST";
    simulateErrorPropagation(plaintext, 8);
    return 0;
}

