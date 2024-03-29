#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

void affineCaesarCipherEncrypt(int a, int b, char *plaintext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            int p = plaintext[i] - 'A';
            int c = (a * p + b) % 26;
            plaintext[i] = 'A' + c;
        }
    }
}

int main() {
    int a, b;
    printf("Enter the value of a (must be co-prime with 26): ");
    scanf("%d", &a);

    // Check if 'a' is co-prime with 26
    if (gcd(a, 26) != 1) {
        printf("Invalid value of 'a'. It must be co-prime with 26.\n");
        return 1;
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    // Check if 'b' lies within the range [0, 25]
    if (b < 0 || b > 25) {
        printf("Invalid value of 'b'. It must be in the range [0, 25].\n");
        return 1;
    }

    char plaintext[100];
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    affineCaesarCipherEncrypt(a, b, plaintext);
    printf("Encrypted text: %s\n", plaintext);

    return 0;
}

