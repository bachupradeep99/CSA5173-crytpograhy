#include <stdio.h>
#include <ctype.h>
#include <string.h>

void polyalphabeticCipher(char text[], char key[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);

    for (int i = 0, j = 0; i < textLen; i++) {
        char ch = text[i];
        if (isalpha(ch)) {
            char offset = isupper(ch) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLen]) - 'a';
            text[i] = (ch - offset + keyChar) % 26 + offset;
            j++;
        }
    }
}

int main() {
    char plaintext[100];
    char key[100];

    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter key: ");
    gets(key);

    polyalphabeticCipher(plaintext, key);
    printf("Ciphertext: %s\n", plaintext);

    return 0;
}

