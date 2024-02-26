#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to perform one-time pad encryption
void oneTimePadVigenere(char *plaintext, int *key, int keyLength) {
    int i;
    int textLength = strlen(plaintext);

    for (i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = (plaintext[i] - base + key[i % keyLength]) % 26 + base;
        }
    }
}

int main() {
    char plaintext[1000];
    int key[1000];
    int keyLength;

    // Get the plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove the newline character from the input
    plaintext[strcspn(plaintext, "\n")] = 0;

    // Get the key from the user
    printf("Enter the key (space-separated integers between 0 and 26): ");
    keyLength = 0;
    while (scanf("%d", &key[keyLength]) == 1) {
        keyLength++;
    }

    // Perform encryption
    oneTimePadVigenere(plaintext, key, keyLength);

    // Display the encrypted text
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
