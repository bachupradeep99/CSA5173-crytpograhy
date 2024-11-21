#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[26] = {0}; // To track used letters
    int row = 0, col = 0;

    // Fill matrix with the keyword
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Treat 'I' and 'J' as the same
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the remaining letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip 'J'
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void formatPlaintext(char plaintext[], char formatted[]) {
    int len = strlen(plaintext);
    int j = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(plaintext[i]);
        if (ch == 'J') ch = 'I'; // Treat 'I' and 'J' as the same
        if (isalpha(ch)) {
            formatted[j++] = ch;
            if (j > 1 && formatted[j - 1] == formatted[j - 2]) {
                formatted[j - 1] = 'X'; // Insert 'X' between duplicates
                i--;
            }
        }
    }
    if (j % 2 != 0) formatted[j++] = 'X'; // Add 'X' if length is odd
    formatted[j] = '\0';
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encryptPair(char matrix[SIZE][SIZE], char ch1, char ch2, char *encrypted) {
    int row1, col1, row2, col2;
    findPosition(matrix, ch1, &row1, &col1);
    findPosition(matrix, ch2, &row2, &col2);

    if (row1 == row2) {
        // Same row: shift right
        encrypted[0] = matrix[row1][(col1 + 1) % SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column: shift down
        encrypted[0] = matrix[(row1 + 1) % SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        // Rectangle: swap corners
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
}

void playfairEncrypt(char plaintext[], char key[]) {
    char matrix[SIZE][SIZE];
    char formatted[100];
    char ciphertext[100] = "";
    int len;

    // Step 1: Create the matrix
    createMatrix(key, matrix);

    // Step 2: Format the plaintext
    formatPlaintext(plaintext, formatted);
    len = strlen(formatted);

    // Step 3: Encrypt each pair
    for (int i = 0; i < len; i += 2) {
        char encrypted[2];
        encryptPair(matrix, formatted[i], formatted[i + 1], encrypted);
        strncat(ciphertext, encrypted, 2);
    }

    // Step 4: Output ciphertext
    printf("Ciphertext: %s\n", ciphertext);
}

int main() {
    char plaintext[100], key[100];

    printf("Enter the plaintext: ");
    gets(plaintext);
    printf("Enter the keyword: ");
    gets(key);

    playfairEncrypt(plaintext, key);

    return 0;
}

