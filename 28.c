#include <stdio.h>

// Function prototypes
int modExp(int base, int exp, int mod);

int main() {
    // Public parameters
    int a = 5;   // Public base
    int q = 23;  // Public modulus

    // Private secrets
    int xA = 6; // Alice's secret
    int xB = 15; // Bob's secret

    // Step 1: Modified exchanges
    int A_prime = xA * a; // Alice sends this
    int B_prime = xB * a; // Bob sends this

    // Step 2: Shared key computation
    int sharedKeyAlice = B_prime * xA; // Alice's computed shared key
    int sharedKeyBob = A_prime * xB;  // Bob's computed shared key

    // Output results
    printf("Public Parameters: a = %d, q = %d\n", a, q);
    printf("Alice's Secret (xA): %d, Bob's Secret (xB): %d\n", xA, xB);
    printf("Alice sends A' = %d, Bob sends B' = %d\n", A_prime, B_prime);
    printf("Shared Key computed by Alice: %d\n", sharedKeyAlice);
    printf("Shared Key computed by Bob: %d\n", sharedKeyBob);

    // Security analysis
    printf("Security Analysis:\n");
    printf("- Using this altered method, Eve can intercept A' and B' easily.\n");
    printf("- Without additional protection, Eve can deduce the shared key K since no modular arithmetic or discrete log is protecting the secrets.\n");
    printf("- Eve can trivially calculate xA or xB by dividing A' or B' by a.\n");

    return 0;
}

