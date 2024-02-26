#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MATRIX_SIZE 2

// Function prototypes
int multiplicativeInverse(int a, int m);
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]);
void modularInverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod, int inverse[MATRIX_SIZE][MATRIX_SIZE]);
void hillEncrypt(const char *message, int cipher[], int key[MATRIX_SIZE][MATRIX_SIZE], int mod);
void hillDecrypt(int cipher[], int decrypted[], int key[MATRIX_SIZE][MATRIX_SIZE], int mod);

// Function to find the multiplicative inverse of a number 'a' modulo 'm'
int multiplicativeInverse(int a, int m) {
    a = a % m;
    int x;
    for ( x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to calculate the modular inverse of a 2x2 matrix
void modularInverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int mod, int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int invDet = multiplicativeInverse(det, mod);
    inverse[0][0] = matrix[1][1] * invDet % mod;
    inverse[0][1] = (-matrix[0][1] * invDet) % mod;
    inverse[1][0] = (-matrix[1][0] * invDet) % mod;
    inverse[1][1] = matrix[0][0] * invDet % mod;
}

// Function to encrypt a message using the Hill cipher
void hillEncrypt(const char *message, int cipher[], int key[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int i;
    for (i = 0; message[i] != '\0'; i += 2) {
        int pair[2] = {message[i] - 'a', message[i + 1] - 'a'};
        cipher[i] = (key[0][0] * pair[0] + key[0][1] * pair[1]) % mod;
        cipher[i + 1] = (key[1][0] * pair[0] + key[1][1] * pair[1]) % mod;
    }
}

// Function to decrypt a message using the Hill cipher
void hillDecrypt(int cipher[], int decrypted[], int key[MATRIX_SIZE][MATRIX_SIZE], int mod) {
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    modularInverse(key, mod, inverse);
    int i;
    for (i = 0; cipher[i] != '\0'; i += 2) {
        int pair[2] = {cipher[i], cipher[i + 1]};
        decrypted[i] = (inverse[0][0] * pair[0] + inverse[0][1] * pair[1]) % mod;
        decrypted[i + 1] = (inverse[1][0] * pair[0] + inverse[1][1] * pair[1]) % mod;
    }
}

int main() {
    const char message[] = "hello";
    int cipher[strlen(message)];
    int decrypted[strlen(message)];
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{3, 2}, {5, 7}};
    int mod = 26;
    int i;

    // Encrypt the message
    hillEncrypt(message, cipher, key, mod);

    // Decrypt the cipher
    hillDecrypt(cipher, decrypted, key, mod);

    // Display the encrypted message
    printf("Encrypted message: ");
    for ( i = 0; i < strlen(message); i++) {
        printf("%c", cipher[i] + 'a');
    }
    printf("\n");

    // Display the decrypted message
    printf("Decrypted message: ");
    for (i = 0; i < strlen(message); i++) {
        printf("%c", decrypted[i] + 'a');
    }
    printf("\n");

    return 0;
}

