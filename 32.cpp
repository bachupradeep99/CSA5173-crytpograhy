#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// Modular exponentiation: (base^exp) % mod
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Modular inverse: a^(-1) mod m (using Extended Euclidean Algorithm)
uint64_t modInverse(uint64_t a, uint64_t m) {
    uint64_t m0 = m, t, q;
    uint64_t x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// DSA signature generation
void DSA_sign(uint64_t messageHash, uint64_t p, uint64_t q, uint64_t g, uint64_t x, uint64_t *r, uint64_t *s) {
    uint64_t k, kInv;
    do {
        k = rand() % (q - 1) + 1; // Random k (1 < k < q)
        *r = modExp(g, k, p) % q; // r = (g^k mod p) mod q
    } while (*r == 0);
    
    kInv = modInverse(k, q); // k^(-1) mod q
    *s = (kInv * (messageHash + x * (*r))) % q; // s = k^(-1) * (H(m) + x * r) mod q
}

// RSA signature generation
uint64_t RSA_sign(uint64_t messageHash, uint64_t d, uint64_t n) {
    return modExp(messageHash, d, n); // S = H(m)^d mod n
}

int main() {
    srand(time(0));

    // Example parameters for DSA
    uint64_t p = 23, q = 11, g = 4; // Prime p, q, and generator g
    uint64_t x = 7; // Private key
    uint64_t messageHash = 9; // Example message hash
    uint64_t r, s;

    // DSA signature generation
    DSA_sign(messageHash, p, q, g, x, &r, &s);
    printf("DSA Signature:\n");
    printf("r = %llu, s = %llu\n", r, s);

    // Example parameters for RSA
    uint64_t n = 55, d = 3; // RSA modulus n and private key d
    uint64_t rsaSignature;

    // RSA signature generation
    rsaSignature = RSA_sign(messageHash, d, n);
    printf("RSA Signature:\n");
    printf("Signature = %llu\n", rsaSignature);

    return 0;
}

