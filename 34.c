#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>

void encrypt_aes_cbc(const char *plaintext, const char *key, const char *iv) {
    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key);

    size_t text_len = strlen(plaintext);
    size_t padded_len = (text_len / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    unsigned char *padded_text = (unsigned char *)calloc(padded_len, sizeof(unsigned char));
    memcpy(padded_text, plaintext, text_len);

    unsigned char ciphertext[padded_len];
    AES_cbc_encrypt(padded_text, ciphertext, padded_len, &aes_key, (unsigned char *)iv, AES_ENCRYPT);

    printf("Ciphertext: ");
    for (size_t i = 0; i < padded_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    free(padded_text);
}

int main() {
    const char *plaintext = "Hello, World!";
    const char *key = "mysecretkey12345";
    const char *iv = "initialvector12";

    encrypt_aes_cbc(plaintext, key, iv);

    return 0;
}
