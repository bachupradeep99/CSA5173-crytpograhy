#include <stdio.h>
#include <string.h>

void oneTimePadEncrypt(char plaintext[], int key[], int len) {
    printf("Ciphertext: ");
    for (int i = 0; i < len; i++) {
        int c = (plaintext[i] - 'a' + key[i]) % 26;
        printf("%c", c + 'a');
    }
    printf("\n");
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 12, 8, 11, 2, 8, 9};
    int len = strlen(plaintext);
    oneTimePadEncrypt(plaintext, key, len);
    return 0;
}

