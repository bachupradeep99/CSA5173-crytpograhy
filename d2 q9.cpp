#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createPlayfairKey(char key[], char playfairMatrix[5][5]) {
    int used[26] = {0};
    int index = 0, x = 0, y = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            playfairMatrix[x][y++] = ch;
            used[ch - 'A'] = 1;
            if (y == 5) {
                y = 0;
                x++;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            playfairMatrix[x][y++] = ch;
            used[ch - 'A'] = 1;
            if (y == 5) {
                y = 0;
                x++;
            }
        }
    } 
}

void displayMatrix(char playfairMatrix[5][5]) {
    printf("Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", playfairMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[100];
    char playfairMatrix[5][5];
    printf("Enter key: ");
    gets(key);

    createPlayfairKey(key, playfairMatrix);
    displayMatrix(playfairMatrix);
    return 0;
}

