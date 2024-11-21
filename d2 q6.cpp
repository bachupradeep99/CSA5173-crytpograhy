#include <stdio.h> 
#include <ctype.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

void decryptAffineCipher(char ciphertext[], int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid value of 'a'. Decryption is not possible.\n");
        return;
    }

    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            int decrypted = (a_inv * (ch - 'A' - b + 26)) % 26;
            printf("%c", decrypted + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[100];
    int a, b;
    printf("Enter ciphertext: ");
    gets(ciphertext);
    printf("Enter values for 'a' and 'b': ");
    scanf("%d %d", &a, &b);

    decryptAffineCipher(ciphertext, a, b);
    return 0;
}
