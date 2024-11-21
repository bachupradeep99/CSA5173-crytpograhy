#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char substitution[]) {
    char ciphertext[100];
    int i;

    // Encrypt each letter
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = substitution[toupper(plaintext[i]) - 'A']; // Substitute letter
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(ciphertext[i]); // Maintain case
            }
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0';

    // Output ciphertext
    printf("Ciphertext: %s\n", ciphertext);
}

int main() {
    char plaintext[100];
    
    // Predefined substitution cipher for 26 letters
    char substitution[26] = {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z', 
        'X', 'C', 'V', 'B', 'N', 'M'
    };

    printf("Enter the plaintext: ");
    gets(plaintext);

    encrypt(plaintext, substitution);

    return 0;
}

