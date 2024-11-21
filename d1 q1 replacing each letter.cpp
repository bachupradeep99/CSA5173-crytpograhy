#include <stdio.h>
#include <ctype.h>

void caesarCipher(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            text[i] = (ch - offset + k) % 26 + offset;
        }
    }
}

int main() {
    char plaintext[100];
    int k;

    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter shift (k): ");
    scanf("%d", &k);

    caesarCipher(plaintext, k);
    printf("Ciphertext: %s\n", plaintext);

    return 0;
}
