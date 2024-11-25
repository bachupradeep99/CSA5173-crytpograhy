#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Example XOR-based encryption function (simplified)
void simpleEncrypt(const uint8_t *input, uint8_t *output, const uint8_t *key, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        output[i] = input[i] ^ key[i];
    }
}

// XOR operation for two blocks
void xorBlocks(const uint8_t *block1, const uint8_t *block2, uint8_t *output, int blockSize) {
    for (int i = 0; i < blockSize; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

// Padding function
int applyPadding(uint8_t *plaintext, int length, int blockSize) {
    int paddingSize = blockSize - (length % blockSize);
    for (int i = 0; i < paddingSize - 1; i++) {
        plaintext[length + i] = 0x00;
    }
    plaintext[length + paddingSize - 1] = 0x80; // Add a '1' bit
    return length + paddingSize;
}

// ECB Mode
void ecbEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, int numBlocks, int blockSize) {
    for (int i = 0; i < numBlocks; i++) {
        simpleEncrypt(plaintext + i * blockSize, ciphertext + i * blockSize, key, blockSize);
    }
}

// CBC Mode
void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, int numBlocks, int blockSize) {
    uint8_t prevCiphertext[8];
    memcpy(prevCiphertext, iv, blockSize);
    for (int i = 0; i < numBlocks; i++) {
        uint8_t tempBlock[8];
        xorBlocks(plaintext + i * blockSize, prevCiphertext, tempBlock, blockSize);
        simpleEncrypt(tempBlock, ciphertext + i * blockSize, key, blockSize);
        memcpy(prevCiphertext, ciphertext + i * blockSize, blockSize);
    }
}

// CFB Mode
void cfbEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, int numBlocks, int blockSize) {
    uint8_t prevCiphertext[8];
    memcpy(prevCiphertext, iv, blockSize);
    for (int i = 0; i < numBlocks; i++) {
        uint8_t tempBlock[8];
        simpleEncrypt(prevCiphertext, tempBlock, key, blockSize);
        xorBlocks(tempBlock, plaintext + i * blockSize, ciphertext + i * blockSize, blockSize);
        memcpy(prevCiphertext, ciphertext + i * blockSize, blockSize);
    }
}

int main() {
    uint8_t key[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
    uint8_t iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t plaintext[64] = "This is a test message for ECB, CBC, and CFB modes";
    uint8_t ciphertext[64] = {0};
    uint8_t decrypted[64] = {0};
    int blockSize = 8;
    int length = strlen((char *)plaintext);
    int paddedLength = applyPadding(plaintext, length, blockSize);
    int numBlocks = paddedLength / blockSize;

    printf("Original Plaintext: %s\n", plaintext);

    // ECB Mode
    printf("\n=== ECB Mode ===\n");
    ecbEncrypt(plaintext, ciphertext, key, numBlocks, blockSize);
    printf("Ciphertext:\n");
    for (int i = 0; i < paddedLength; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // CBC Mode
    printf("\n=== CBC Mode ===\n");
    memset(ciphertext, 0, sizeof(ciphertext));
    cbcEncrypt(plaintext, ciphertext, key, iv, numBlocks, blockSize);
    printf("Ciphertext:\n");
    for (int i = 0; i < paddedLength; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // CFB Mode
    printf("\n=== CFB Mode ===\n");
    memset(ciphertext, 0, sizeof(ciphertext));
    cfbEncrypt(plaintext, ciphertext, key, iv, numBlocks, blockSize);
    printf("Ciphertext:\n");
    for (int i = 0; i < paddedLength; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

