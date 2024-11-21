#include <stdio.h>
#include <string.h>
#include <ctype.h>

void prepareText(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len - 1; i += 2) {
        if (text[i] == text[i + 1]) {
            memmove(&text[i + 2], &text[i + 1], len - i);
            text[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        text[len] = 'X';
        text[len + 1] = '\0';
    }
}

void encryptPlayfairCipher(char plaintext[], char playfairMatrix[5][5]) {
    // Implementation based on Playfair encryption rules
}

int main() {
    char plaintext[100], key[100], playfairMatrix[5][5];
    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter key: ");
    gets(key);

    prepareText(plaintext);
    printf("Prepared Text: %s\n", plaintext);

    // Generate and encrypt using Playfair cipher
    return 0;
}
 
