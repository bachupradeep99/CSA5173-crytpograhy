#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void letterFrequencyAttack(char ciphertext[], int topN) {
    int freq[ALPHABET_SIZE] = {0};
    int len = strlen(ciphertext);

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }

    // Display the top N possible plaintexts
    printf("Top %d possible plaintexts:\n", topN);
    for (int k = 0; k < topN; k++) {
        printf("Key %d: ", k);
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                char ch = toupper(ciphertext[i]);
                printf("%c", (ch - 'A' - k + ALPHABET_SIZE) % ALPHABET_SIZE + 'A');
            } else {
                printf("%c", ciphertext[i]);
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[] = "UJBBUJIFEF"; // Example ciphertext
    int topN = 10;
    printf("Ciphertext: %s\n", ciphertext);
    letterFrequencyAttack(ciphertext, topN);
    return 0;
}

