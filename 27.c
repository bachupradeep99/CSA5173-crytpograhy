#include <stdio.h>
#include <math.h>

// Function prototypes
long long modExp(long long base, long long exp, long long mod);

int main() {
    // RSA public key
    long long e = 7;  // Public key exponent
    long long n = 187; // Modulus (example, usually very large)

    // Example ciphertext
    long long ciphertext[] = {23, 67, 104}; // Example encrypted characters
    int numCiphertext = sizeof(ciphertext) / sizeof(ciphertext[0]);

    // Step 1: Precompute all possible ciphertexts for plaintext values 0-25
    long long precomputed[26];
    for (int m = 0; m < 26; m++) {
        precomputed[m] = modExp(m, e, n); // Encrypt each possible plaintext
    }

    // Step 2: Match ciphertexts to precomputed values
    printf("Decrypted message: uyutnhh");
    for (int i = 0; i < numCiphertext; i++) {
        for (int m = 0; m < 26; m++) {
            if (ciphertext[i] == precomputed[m]) {
                printf("%c", 'A' + m); // Print corresponding plaintext character
                break;
            }
        }
    }
    printf("\n");

    return 0;
}

// Modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) // If exp is odd
            result = (result * base) % mod;
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

