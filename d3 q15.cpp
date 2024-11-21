#include <stdio.h>
#include <string.h>
#include <ctype.h> 

void frequencyAttack(char ciphertext[]) {
    int freq[26] = {0};
    int i;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) { 
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
    int maxFreq = 0, commonLetter = 0;
    for (i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            commonLetter = i;
        }
    }

    int key = (commonLetter - ('E' - 'A') + 26) % 26; 
    printf("Possible key: %d\n", key);

    printf("Decrypted Text: ");
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]); 
            printf("%c", (ch - 'A' - key + 26) % 26 + 'A'); 
        } else {
            printf("%c", ciphertext[i]); 
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[100]; 
    printf("Enter the ciphertext (uppercase letters only): ");
    scanf("%s", ciphertext); 
    frequencyAttack(ciphertext); 
    return 0;
}

