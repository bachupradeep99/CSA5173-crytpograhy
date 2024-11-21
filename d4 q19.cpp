#include <stdio.h>
#include <string.h>

void xorBlocks(char *block1, char *block2, int len) {
    for (int i = 0; i < len; i++) {
        block1[i] ^= block2[i];
    }
}

void encryptCBC(char plaintext[], char iv[], int blockSize) {
    char currentBlock[blockSize];
    char prevCiphertext[blockSize];
    memcpy(prevCiphertext, iv, blockSize);

    printf("Ciphertext:\n");
    for (int i = 0; i < strlen(plaintext); i += blockSize) {
        memcpy(currentBlock, plaintext + i, blockSize);
        xorBlocks(currentBlock, prevCiphertext, blockSize);

        // Encrypt currentBlock here (placeholder for actual encryption)
        memcpy(prevCiphertext, currentBlock, blockSize);

        // Print encrypted block
        for (int j = 0; j < blockSize; j++) {
            printf("%02X ", (unsigned char)prevCiphertext[j]);
        }
        printf("\n");
    }
}

int main() {
    char plaintext[] = "THISISACBCMODETEST";
    char iv[] = "INITVECT"; // Initialization vector
    encryptCBC(plaintext, iv, 8);
    return 0;
}

