#include <stdio.h>
#include <stdlib.h>

#define MESSAGE "Hello, world!"

int main() {
    // DSA key generation
    DSA *dsa = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    if (dsa == NULL) {
        fprintf(stderr, "Error generating DSA parameters\n");
        return 1;
    }
    DSA_generate_key(dsa);

    // RSA key generation
    RSA *rsa = RSA_generate_key(1024, RSA_F4, NULL, NULL);
    if (rsa == NULL) {
        fprintf(stderr, "Error generating RSA key\n");
        return 1;
    }

    // DSA signing
    unsigned char dsa_signature[DSA_size(dsa)];
    DSA_sign(0, (const unsigned char *)MESSAGE, sizeof(MESSAGE), dsa_signature, NULL, dsa);

    // RSA signing
    unsigned char rsa_signature[1024];
    unsigned int rsa_signature_len;
    RSA_sign(NID_sha256, (const unsigned char *)MESSAGE, sizeof(MESSAGE), rsa_signature, &rsa_signature_len, rsa);

    // Print signatures
    printf("DSA signature: ");
    for (int i = 0; i < sizeof(dsa_signature); i++) {
        printf("%02X", dsa_signature[i]);
    }
    printf("\n");

    printf("RSA signature: ");
    for (int i = 0; i < rsa_signature_len; i++) {
        printf("%02X", rsa_signature[i]);
    }
    printf("\n");

    // Clean up
    DSA_free(dsa);
    RSA_free(rsa);

    return 0;
}

