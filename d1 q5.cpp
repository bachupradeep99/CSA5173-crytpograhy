#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void affineCipher(char text[], int a, int b) {
    if (gcd(a, 26) != 1) {
        printf("Invalid 'a' value. It must be coprime with 26.\n");
        return;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            text[i] = ((a * (ch - offset) + b) % 26 + 26) % 26 + offset; // Handle negatives
        }
    }
}

int main() {
    char plaintext[100];
    int a, b;

    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    affineCipher(plaintext, a, b);
    printf("Ciphertext: %s\n", plaintext);

    return 0;
}

