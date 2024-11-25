#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Simplified CBC-MAC for demonstration (using XOR for simplicity)
#define BLOCK_SIZE 16 // Assume 16-byte blocks

// XOR based encryption (simplified for the purpose of CBC-MAC)
void xorEncrypt(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i]; // XOR with the key
    }
}

// Function to compute CBC MAC
void cbcMac(uint8_t *message, size_t messageLength, uint8_t *key, uint8_t *mac) {
    uint8_t block[BLOCK_SIZE] = {0}; // Initializing the block to zero (IV)
    size_t numBlocks = messageLength / BLOCK_SIZE;
    
    for (size_t i = 0; i < numBlocks; i++) {
        // XOR the current message block with the previous block (or IV for first block)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= message[i * BLOCK_SIZE + j];
        }

        // Encrypt the block
        xorEncrypt(block, key);
    }
    
    // The final block is the CBC MAC
    memcpy(mac, block, BLOCK_SIZE);
}

// Function to demonstrate the attack: Given CBC MAC for X, adversary can create MAC for X || T
void attack(uint8_t *message, size_t messageLength, uint8_t *mac) {
    printf("Original Message: ");
    for (size_t i = 0; i < messageLength; i++) {
        printf("%02x ", message[i]);
    }
    printf("\nOriginal MAC (T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", mac[i]);
    }
    printf("\n");

    // Now the adversary appends MAC to the message to form X || T
    uint8_t messageWithMac[messageLength + BLOCK_SIZE];
    memcpy(messageWithMac, message, messageLength);
    memcpy(messageWithMac + messageLength, mac, BLOCK_SIZE);

    // Display the modified message
    printf("Modified Message (X || T): ");
    for (size_t i = 0; i < messageLength + BLOCK_SIZE; i++) {
        printf("%02x ", messageWithMac[i]);
    }
    printf("\n");
    
    // Recompute the MAC for X || T (which will be valid)
    uint8_t newMac[BLOCK_SIZE];
    cbcMac(messageWithMac, messageLength + BLOCK_SIZE, mac, newMac); // Use original MAC as key for simplicity

    // Show the valid new MAC
    printf("Valid MAC for X || T: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", newMac[i]);
    }
    printf("\n");
}

int main() {
    // Example 128-bit key (simplified for demonstration)
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

    // Example message (X) - 32 bytes (2 blocks)
    uint8_t message[32] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
                           0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60};

    // Compute the CBC MAC for the message X
    uint8_t mac[BLOCK_SIZE] = {0};
    cbcMac(message, sizeof(message), key, mac);

    // Display the attack result (how an adversary can generate a valid MAC for X || T)
    attack(message, sizeof(message), mac);

    return 0;
}

