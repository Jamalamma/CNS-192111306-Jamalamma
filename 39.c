#include <stdio.h>
#include <string.h>

void decrypt(char ciphertext[], int key) {
    int length = strlen(ciphertext);

    printf("Possible plaintexts for key %d:\n", key);

    for (int i = 0; i < length; i++) {
        char decryptedChar = ciphertext[i] - key;

        // Ensure the character is in the valid range (A-Z)
        if (decryptedChar < 'A') {
            decryptedChar += 26;
        }

        printf("%c", decryptedChar);
    }

    printf("\n");
}

int main() {
    char ciphertext[1000];
    int key;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("Enter the number of possible plaintexts to generate: ");
    scanf("%d", &key);

    // Perform frequency attack for all possible keys
    for (int i = 1; i <= key; i++) {
        decrypt(ciphertext, i);
    }

    return 0;
}
