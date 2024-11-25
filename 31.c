#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 16 // AES block size (128 bits)
#define BLOCK_SIZE_64 8 // 64 bits block size

// Constant for 128-bit block size (AES)
#define R128 0x87 

// Constant for 64-bit block size
#define R64 0x1B

void left_shift(uint8_t *block, int block_size) {
    int i;
    uint8_t carry = 0;
    for (i = 0; i < block_size; i++) {
        uint8_t new_carry = (block[i] >> 7) & 0x01;
        block[i] = (block[i] << 1) | carry;
        carry = new_carry;
    }
}

void xor_with_constant(uint8_t *block, uint8_t constant, int block_size) {
    block[0] ^= constant;
}

void generate_subkeys(uint8_t *key, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t block[BLOCK_SIZE] = {0};
    int i;
    
    // Step 1: Apply block cipher to the block of all zeros
    // In practice, you would encrypt the block using AES or another block cipher.
    // We just assume this gives a block with zero values for simplicity.
    
    // Step 2: Generate K1 (first subkey)
    // First, left shift by one bit
    left_shift(block, block_size);
    
    // Check the MSB of the block, if it's 1, XOR with the constant
    if (block[0] & 0x80) {
        xor_with_constant(block, R128, block_size);  // Change to R64 if 64-bit block
    }
    for (i = 0; i < block_size; i++) {
        K1[i] = block[i];
    }

    // Step 3: Generate K2 (second subkey)
    // Left shift K1 by one bit
    left_shift(K1, block_size);
    
    // Check MSB of K1, and XOR with the constant if necessary
    if (K1[0] & 0x80) {
        xor_with_constant(K1, R128, block_size);  // Change to R64 if 64-bit block
    }
    
    for (i = 0; i < block_size; i++) {
        K2[i] = K1[i];
    }
}

void print_block(uint8_t *block, int block_size) {
    int i;
    for (i = 0; i < block_size; i++) {
        printf("%02x ", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t K1[BLOCK_SIZE] = {0};  // First subkey
    uint8_t K2[BLOCK_SIZE] = {0};  // Second subkey
    
    uint8_t key[BLOCK_SIZE] = {0};  // Block cipher key (not used here for simplicity)
    
    // Generate subkeys
    generate_subkeys(key, K1, K2, BLOCK_SIZE);
    
    // Print the subkeys
    printf("K1 (first subkey): ");
    print_block(K1, BLOCK_SIZE);
    
    printf("K2 (second subkey): ");
    print_block(K2, BLOCK_SIZE);
    
    return 0;
}
