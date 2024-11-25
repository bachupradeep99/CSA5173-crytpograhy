#include <stdio.h>

// Function prototypes
int gcd(int a, int b);
int gcdExtended(int a, int b, int *x, int *y);
long long modExp(long long base, long long exp, long long mod);

int main() {
    // Input values
    int n = 3599;  // Modulus
    int e = 31;    // Public key exponent
    int M = 59;    // Example plaintext block with a common factor with n

    // Step 1: Compute GCD(M, n)
    int p = gcd(M, n);

    if (p > 1) {
        // Step 2: Factorization
        int q = n / p;
        printf("Factors of n: p = %d, q = %d\n", p, q);

        // Step 3: Compute f(n)
        int phi = (p - 1) * (q - 1);
        printf("f(n): %d\n", phi);

        // Step 4: Find private key (d)
        int x, y;
        gcdExtended(e, phi, &x, &y);
        int d = (x % phi + phi) % phi; // Ensure d is positive
        printf("Private key (d): %d\n", d);

        // Example ciphertext
        long long ciphertext = 855; // Example ciphertext block
        long long decrypted = modExp(ciphertext, d, n);

        printf("Ciphertext: %lld\n", ciphertext);
        printf("Decrypted Plaintext: %lld\n", decrypted);
    } else {
        printf("No common factor found between M and n.\n");
    }

    return 0;
}

// Compute GCD of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
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

