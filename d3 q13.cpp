#include <stdio.h>
#include <stdlib.h>

#define MOD 26

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[2][2]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

// Function to calculate modular inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse exists
}

// Function to compute the inverse of a 2x2 matrix modulo 26
void inverseMatrix(int matrix[2][2], int inverse[2][2]) {
    int det = determinant(matrix);
    int detInverse = modInverse(det % MOD, MOD);
    if (detInverse == -1) {
        printf("Matrix is not invertible under mod 26.\n");
        exit(1);
    }

    // Calculate the adjugate matrix
    inverse[0][0] = matrix[1][1];
    inverse[1][1] = matrix[0][0];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];

    // Apply modulo 26 to all elements
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inverse[i][j] = (inverse[i][j] * detInverse) % MOD;
            if (inverse[i][j] < 0) { // Ensure positive values
                inverse[i][j] += MOD;
            }
        }
    }
}

// Function to multiply two 2x2 matrices modulo 26
void matrixMultiply(int A[2][2], int B[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
            result[i][j] %= MOD;
        }
    }
}

int main() {
    int plaintextMatrix[2][2], ciphertextMatrix[2][2];
    int inversePlaintext[2][2], keyMatrix[2][2];

    // Input plaintext-ciphertext pairs
    printf("Enter the 2x2 plaintext matrix (mod 26):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &plaintextMatrix[i][j]);
        }
    }

    printf("Enter the 2x2 ciphertext matrix (mod 26):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &ciphertextMatrix[i][j]);
        }
    }

    // Calculate the inverse of the plaintext matrix
    inverseMatrix(plaintextMatrix, inversePlaintext);

    // Calculate the key matrix: Key = Inverse(Plaintext) * Ciphertext
    matrixMultiply(inversePlaintext, ciphertextMatrix, keyMatrix);

    // Output the key matrix
    printf("Recovered Key Matrix (mod 26):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

