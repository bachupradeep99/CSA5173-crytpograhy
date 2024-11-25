#include <stdio.h>
#include <math.h>

// Function prototypes
int gcdExtended(int a, int b, int *x, int *y);
long long modExp(long long base, long long exp, long long mod);

int main() {
    // Public key values
    int e = 31, n = 3599;
    int p, q, phi, d;

    // Step 1: Factorize n to find p and q
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Compute f(n)
    phi = (p - 1) * (q - 1);

    // Step 2: Use Extended Euclidean Algorithm to find d
    int x, y;
    gcdExtended(e, phi, &x, &y);
    d = (x % phi + phi) % phi; // Ensure d is positive

    // Display results
    printf("Factors of n: p = %d, q = %d\n", p, q);
    printf("f(n): %d\n", phi);
    printf("Private key (d): %d\n", d);

    // Encryption and Decryption
    long long plaintext = 123; // Example plaintext
    long long ciphertext = modExp(plaintext, e, n);
    long long decrypted = modExp(ciphertext, d, n);

    printf("Plaintext: %lld\n", plaintext);
    printf("Ciphertext: %lld\n", ciphertext);
    printf("Decrypted Plaintext: %lld\n", decrypted);

    return 0;
}

// Extended Euclidean Algorithm to find modular inverse
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
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

