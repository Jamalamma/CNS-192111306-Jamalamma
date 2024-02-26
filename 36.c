#include <stdio.h>
#include <ctype.h>

// Function to encrypt a single character using the affine Caesar cipher
char encrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return ((a * (ch - base) + b) % 26) + base;
    }
    return ch;
}

// Function to encrypt a string using the affine Caesar cipher
void encryptString(char *str, int a, int b) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = encrypt(str[i], a, b);
    }
}

int main() {
    int a, b;

    // Get values for 'a' and 'b' from the user
    printf("Enter the value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    // Check if 'a' is coprime with 26
    if (a % 2 == 0 || a % 13 == 0) {
        printf("Error: 'a' must be coprime with 26.\n");
        return 1;
    }

    // Get the plaintext from the user
    char plaintext[100];
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    // Encrypt the plaintext
    encryptString(plaintext, a, b);

    // Display the encrypted text
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
