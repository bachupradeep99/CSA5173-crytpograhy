#include <stdio.h>
#include <string.h> 

void hillEncrypt(char plaintext[], int key[2][2]) {
    int len = strlen(plaintext);
    
    // Ensure plaintext length is even by padding with 'x' if needed
    if (len % 2 != 0) {
        plaintext[len] = 'x';
        plaintext[len + 1] = '\0'; // Null-terminate the string
        len++;
    }

    printf("Ciphertext: ");
    for (int i = 0; i < len; i += 2) {
        int x1 = plaintext[i] - 'a';
        int x2 = plaintext[i + 1] - 'a';
        int c1 = (key[0][0] * x1 + key[0][1] * x2) % 26;
        int c2 = (key[1][0] * x1 + key[1][1] * x2) % 26;
        printf("%c%c", c1 + 'a', c2 + 'a');
    }
    printf("\n");
}

int main() {
    char plaintext[100];
    int key[2][2] = {{9, 4}, {5, 7}};

    printf("Enter the plaintext (lowercase letters only): ");
    scanf("%s", plaintext);

    hillEncrypt(plaintext, key);
    return 0;
}

