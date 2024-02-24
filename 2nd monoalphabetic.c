#include <stdio.h>
#include <string.h>

void encrypt(char *plaintext, char *ciphertext, char *message) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        if (message[i] >= 'a' && message[i] <= 'z') {
            message[i] = ciphertext[message[i] - 'a'];
        } else if (message[i] >= 'A' && message[i] <= 'Z') {
            message[i] = ciphertext[message[i] - 'A'] + 'A' - 'a';
        }
    }
}

int main() {
    char plaintext[] = "abcdefghijklmnopqrstuvwxyz";
    char ciphertext[] = "XPMGTDHLYONZBWEARKJUFSCIQV";
    char message[100];

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    encrypt(plaintext, ciphertext, message);

    printf("Encrypted message: %s\n", message);

    return 0;
}
