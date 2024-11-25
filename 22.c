#include <stdio.h>
#include <string.h>

// S-DES constants for simplicity
#define BLOCK_SIZE 8
#define KEY_SIZE 10
#define SUBKEY_SIZE 8

// Function prototypes
void generateSubkeys(const char *key, char *k1, char *k2);
void sdesEncrypt(const char *plaintext, char *ciphertext, const char *subkey);
void sdesDecrypt(const char *ciphertext, char *plaintext, const char *subkey);
void xorBlocks(const char *block1, const char *block2, char *output);
void cbcEncrypt(const char *plaintext, char *ciphertext, const char *key, const char *iv, int numBlocks);
void cbcDecrypt(const char *ciphertext, char *plaintext, const char *key, const char *iv, int numBlocks);

int main() {
    // Input parameters
    char plaintext[] = "0000000100100011"; // Binary plaintext
    char key[] = "0111111101";           // Binary key
    char iv[] = "10101010";              // Binary IV
    char ciphertext[BLOCK_SIZE * 2] = {0};
    char decrypted[BLOCK_SIZE * 2] = {0};

    // Ensure plaintext length is a multiple of the block size
    int length = strlen(plaintext);
    int numBlocks = length / BLOCK_SIZE;

    // Encryption and decryption in CBC mode
    printf("Original Plaintext: %s\n", plaintext);
    cbcEncrypt(plaintext, ciphertext, key, iv, numBlocks);
    printf("Ciphertext: %s\n", ciphertext);
    cbcDecrypt(ciphertext, decrypted, key, iv, numBlocks);
    printf("Decrypted Plaintext: %s\n", decrypted);

    return 0;
}

void generateSubkeys(const char *key, char *k1, char *k2) {
    // Example key generation logic for S-DES (simplified for demonstration)
    strncpy(k1, key, SUBKEY_SIZE);
    strncpy(k2, key + 2, SUBKEY_SIZE);
}

void sdesEncrypt(const char *plaintext, char *ciphertext, const char *subkey) {
    // Simplified S-DES encryption (replace with actual S-DES logic)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ subkey[i % SUBKEY_SIZE];
    }
}

void sdesDecrypt(const char *ciphertext, char *plaintext, const char *subkey) {
    // Simplified S-DES decryption (same as encryption for demonstration)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ subkey[i % SUBKEY_SIZE];
    }
}

void xorBlocks(const char *block1, const char *block2, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = (block1[i] - '0') ^ (block2[i] - '0') + '0';
    }
}

void cbcEncrypt(const char *plaintext, char *ciphertext, const char *key, const char *iv, int numBlocks) {
    char ivTemp[BLOCK_SIZE];
    char subkey1[SUBKEY_SIZE], subkey2[SUBKEY_SIZE];
    char tempBlock[BLOCK_SIZE];

    generateSubkeys(key, subkey1, subkey2);
    strncpy(ivTemp, iv, BLOCK_SIZE);

    for (int i = 0; i < numBlocks; i++) {
        xorBlocks(plaintext + i * BLOCK_SIZE, ivTemp, tempBlock);
        sdesEncrypt(tempBlock, ciphertext + i * BLOCK_SIZE, subkey1);
        strncpy(ivTemp, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void cbcDecrypt(const char *ciphertext, char *plaintext, const char *key, const char *iv, int numBlocks) {
    char ivTemp[BLOCK_SIZE];
    char subkey1[SUBKEY_SIZE], subkey2[SUBKEY_SIZE];
    char tempBlock[BLOCK_SIZE];

    generateSubkeys(key, subkey1, subkey2);
    strncpy(ivTemp, iv, BLOCK_SIZE);

    for (int i = 0; i < numBlocks; i++) {
        sdesDecrypt(ciphertext + i * BLOCK_SIZE, tempBlock, subkey1);
        xorBlocks(tempBlock, ivTemp, plaintext + i * BLOCK_SIZE);
        strncpy(ivTemp, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

