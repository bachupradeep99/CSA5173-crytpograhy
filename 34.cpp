#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // Block size in bytes

// Dummy block cipher function (for demonstration purposes)
void blockCipher(uint8_t *input, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; // XOR with the key as a basic example
    }
}

// Padding function
void pad(uint8_t *data, int *len) {
    int padding = BLOCK_SIZE - (*len % BLOCK_SIZE);
    for (int i = 0; i < padding; i++) {
        data[*len + i] = (i == 0) ? 0x80 : 0x00; // Append 1 bit followed by 0s
    }
    *len += padding;
}

// ECB Mode Encryption
void ECBEncrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        blockCipher(&plaintext[i], key, &ciphertext[i]);
    }
}

// CBC Mode Encryption
void CBCEncrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t prevBlock[BLOCK_SIZE];
    memcpy(prevBlock, iv, BLOCK_SIZE); // Initialize with IV

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        // XOR current plaintext block with the previous ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= prevBlock[j];
        }
        // Encrypt the result
        blockCipher(&plaintext[i], key, &ciphertext[i]);
        // Update the previous block to the current ciphertext block
        memcpy(prevBlock, &ciphertext[i], BLOCK_SIZE);
    }
}

// CFB Mode Encryption
void CFBEncrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t shiftRegister[BLOCK_SIZE];
    memcpy(shiftRegister, iv, BLOCK_SIZE); // Initialize with IV

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        uint8_t keystream[BLOCK_SIZE];
        // Encrypt the shift register to produce the keystream
        blockCipher(shiftRegister, key, keystream);

        for (int j = 0; j < BLOCK_SIZE; j++) {
            // XOR the keystream with the plaintext
            ciphertext[i + j] = plaintext[i + j] ^ keystream[j];
            // Update the shift register with the resulting ciphertext
            shiftRegister[j] = ciphertext[i + j];
        }
    }
}

int main() {
    uint8_t plaintext[64] = "Example message for ECB, CBC, and CFB modes.";
    uint8_t key[BLOCK_SIZE] = {'m', 'y', 'k', 'e', 'y', '1', '2', '3'}; // Proper key initialization
    uint8_t iv[BLOCK_SIZE] = {'i', 'n', 'i', 't', 'v', 'e', 'c', 't'};  // Example IV
    uint8_t ciphertext[64];
    int len = strlen((char *)plaintext);

    printf("Original Plaintext: %s\n", plaintext);

    // Padding the plaintext
    pad(plaintext, &len);

    // ECB Encryption
    ECBEncrypt(plaintext, len, key, ciphertext);
    printf("\nECB Ciphertext: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext[i]);

    // Reset plaintext and reinitialize for CBC
    memcpy(plaintext, "Example message for ECB, CBC, and CFB modes.", len);

    // CBC Encryption
    CBCEncrypt(plaintext, len, key, iv, ciphertext);
    printf("\n\nCBC Ciphertext: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext[i]);

    // Reset plaintext and reinitialize for CFB
    memcpy(plaintext, "Example message for ECB, CBC, and CFB modes.", len);

    // CFB Encryption
    CFBEncrypt(plaintext, len, key, iv, ciphertext);
    printf("\n\nCFB Ciphertext: ");
    for (int i = 0; i < len; i++) printf("%02x ", ciphertext[i]);

    printf("\n");
    return 0;
}

