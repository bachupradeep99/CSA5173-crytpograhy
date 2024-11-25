#include <stdio.h>
#include <string.h>

// Constants for S-DES
#define BLOCK_SIZE 8
#define KEY_SIZE 10
#define SUBKEY_SIZE 8

// Function prototypes
void generateSubkeys(const char *key, char *k1, char *k2);
void sdesEncrypt(const char *input, char *output, const char *subkey);
void xorBlocks(const char *block1, const char *block2, char *output);
void incrementCounter(char *counter);
void ctrEncryptDecrypt(const char *input, char *output, const char *key, char *counter, int numBlocks);

int main() {
    // Input parameters
    char plaintext[] = "000000010000001000000100"; // Binary plaintext
    char key[] = "0111111101";                   // Binary key
    char counter[] = "00000000";                 // Initial counter
    char ciphertext[BLOCK_SIZE * 3] = {0};
    char decrypted[BLOCK_SIZE * 3] = {0};

    int length = strlen(plaintext);
    int numBlocks = length / BLOCK_SIZE;

    // Encryption and decryption in CTR mode
    printf("Original Plaintext: %s\n", plaintext);
    ctrEncryptDecrypt(plaintext, ciphertext, key, counter, numBlocks);
    printf("Ciphertext: %s\n", ciphertext);

    // Reset counter for decryption
    strcpy(counter, "00000000");
    ctrEncryptDecrypt(ciphertext, decrypted, key, counter, numBlocks);
    printf("Decrypted Plaintext: %s\n", decrypted);

    return 0;
}

void generateSubkeys(const char *key, char *k1, char *k2) {
    // Simplified S-DES key generation
    strncpy(k1, key, SUBKEY_SIZE);
    strncpy(k2, key + 2, SUBKEY_SIZE);
}

void sdesEncrypt(const char *input, char *output, const char *subkey) {
    // Simplified S-DES encryption (replace with actual S-DES logic)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ subkey[i % SUBKEY_SIZE];
    }
}

void xorBlocks(const char *block1, const char *block2, char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = (block1[i] - '0') ^ (block2[i] - '0') + '0';
    }
}

void incrementCounter(char *counter) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        if (counter[i] == '0') {
            counter[i] = '1';
            break;
        } else {
            counter[i] = '0';
        }
    }
}

void ctrEncryptDecrypt(const char *input, char *output, const char *key, char *counter, int numBlocks) {
    char subkey1[SUBKEY_SIZE], subkey2[SUBKEY_SIZE];
    char keystream[BLOCK_SIZE];
    char tempCounter[BLOCK_SIZE];

    generateSubkeys(key, subkey1, subkey2);

    for (int i = 0; i < numBlocks; i++) {
        // Encrypt the counter to generate the keystream
        strncpy(tempCounter, counter, BLOCK_SIZE);
        sdesEncrypt(tempCounter, keystream, subkey1);

        // XOR keystream with input block
        xorBlocks(input + i * BLOCK_SIZE, keystream, output + i * BLOCK_SIZE);

        // Increment the counter
        incrementCounter(counter);
    }
}

