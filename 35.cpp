#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Encrypts plaintext using the Vigen�re cipher with the given key stream
void encryptVigenere(const char *plaintext, int *keyStream, int keyLength, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') { // Lowercase letters
            ciphertext[i] = ((plaintext[i] - 'a' + keyStream[i % keyLength]) % ALPHABET_SIZE) + 'a';
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') { // Uppercase letters
            ciphertext[i] = ((plaintext[i] - 'A' + keyStream[i % keyLength]) % ALPHABET_SIZE) + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }3  
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
}

// Decrypts ciphertext using the Vigen�re cipher with the given key stream
void decryptVigenere(const char *ciphertext, int *keyStream, int keyLength, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') { // Lowercase letters
            plaintext[i] = ((ciphertext[i] - 'a' - keyStream[i % keyLength] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') { // Uppercase letters
            plaintext[i] = ((ciphertext[i] - 'A' - keyStream[i % keyLength] + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext
}

// Generates a random key stream of a given length
void generateKeyStream(int *keyStream, int length) {
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < length; i++) {
        keyStream[i] = rand() % ALPHABET_SIZE; // Generate random numbers between 0 and 25
    }
}

// Main function
int main() {
    char plaintext[256] = "Send more money"; // Input plaintext
    char ciphertext[256];
    char decryptedText[256];
    int keyStream[256];
    int keyLength = strlen(plaintext); // Key length matches plaintext length

    // Generate a random key stream
    generateKeyStream(keyStream, keyLength);

    // Display the key stream
    printf("Key Stream: ");
    for (int i = 0; i < keyLength; i++) {
        printf("%d ", keyStream[i]);
    }
    printf("\n");

    // Encrypt the plaintext
    encryptVigenere(plaintext, keyStream, keyLength, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decryptVigenere(ciphertext, keyStream, keyLength, decryptedText);
    printf("Decrypted Plaintext: %s\n", decryptedText);

    return 0;
}

