#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptSubstitutionCipher(char ciphertext[], char substitution[]) {
    char reverseSubstitution[26];
    for (int i = 0; i < 26; i++) {
        reverseSubstitution[substitution[i] - 'A'] = 'A' + i;
    }

    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]); // Convert to uppercase
            printf("%c", reverseSubstitution[ch - 'A']);
        } else {
            printf("%c", ciphertext[i]); // Preserve non-alphabetic characters
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[100];
    char substitution[] = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; // Reverse alphabet substitution cipher

    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin); // Safe input method
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline

    decryptSubstitutionCipher(ciphertext, substitution);
    return 0;
}

