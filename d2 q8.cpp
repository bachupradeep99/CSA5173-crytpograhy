#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createCipherKey(char keyword[], char cipherKey[]) {
    int used[26] = {0};
    int index = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipherKey[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherKey[index++] = ch;
        }
    }
    cipherKey[index] = '\0';
}

void encryptMonoalphabeticCipher(char plaintext[], char cipherKey[]) {
    printf("Encrypted Text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            printf("%c", cipherKey[ch - 'A']);
        } else {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n"); 
}

int main() {
    char plaintext[100], keyword[100], cipherKey[27];
    printf("Enter plaintext: ");
    gets(plaintext);
    printf("Enter keyword: ");
    gets(keyword);

    createCipherKey(keyword, cipherKey);
    printf("Cipher Key: %s\n", cipherKey);
    encryptMonoalphabeticCipher(plaintext, cipherKey);
    return 0;
}

