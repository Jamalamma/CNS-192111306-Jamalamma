#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // Assume 64-bit blocks for simplicity

// Function prototypes
void ECB_encrypt(uint64_t plaintext[], uint64_t key[], int num_blocks);
void ECB_decrypt(uint64_t ciphertext[], uint64_t key[], int num_blocks);
void CBC_encrypt(uint64_t plaintext[], uint64_t key[], uint64_t iv, int num_blocks);
void CBC_decrypt(uint64_t ciphertext[], uint64_t key[], uint64_t iv, int num_blocks);
void print_blocks(uint64_t blocks[], int num_blocks);

int main() {
    // Example plaintext and key
    uint64_t plaintext[] = {0x0123456789ABCDEF, 0xFEDCBA9876543210}; // Two 64-bit blocks
    uint64_t key[] = {0x133457799BBCDFF1}; // 64-bit key
    uint64_t iv = 0x0000000000000000; // Initialization vector (for CBC mode)

    // ECB mode encryption
    printf("ECB mode encryption:\n");
    ECB_encrypt(plaintext, key, 2); // Encrypt two blocks
    printf("\n");

    // CBC mode encryption
    printf("CBC mode encryption:\n");
    CBC_encrypt(plaintext, key, iv, 2); // Encrypt two blocks
    printf("\n");

    // Simulate error in the first ciphertext block (for CBC mode)
    printf("Simulating error in the first ciphertext block (for CBC mode)...\n");
    plaintext[0] ^= 0x0000000000000001; // Introduce a bit error in the first plaintext block

    // CBC mode decryption (with error in first ciphertext block)
    printf("CBC mode decryption (with error in first ciphertext block):\n");
    CBC_decrypt(plaintext, key, iv, 2); // Decrypt two blocks

    return 0;
}

// Function to encrypt plaintext using ECB mode
void ECB_encrypt(uint64_t plaintext[], uint64_t key[], int num_blocks) {
    printf("Plaintext blocks:\n");
    print_blocks(plaintext, num_blocks);

    // Encryption process (simplified)
    printf("Encrypting using ECB mode...\n");
    printf("Ciphertext blocks:\n");
    int i;
    // Perform encryption of each block independently
    for (i = 0; i < num_blocks; i++) {
        // Simplified encryption process (just XOR with key for demonstration)
        uint64_t ciphertext_block = plaintext[i] ^ key[0]; // Example: XOR with key
        printf("%016lx\n", ciphertext_block);
    }
}

// Function to decrypt ciphertext using ECB mode
void ECB_decrypt(uint64_t ciphertext[], uint64_t key[], int num_blocks) {
    printf("Ciphertext blocks:\n");
    print_blocks(ciphertext, num_blocks);

    // Decryption process (simplified)
    printf("Decrypting using ECB mode...\n");
    printf("Decrypted plaintext blocks:\n");
    int i;
    // Perform decryption of each block independently
    for ( i = 0; i < num_blocks; i++) {
        // Simplified decryption process (just XOR with key for demonstration)
        uint64_t plaintext_block = ciphertext[i] ^ key[0]; // Example: XOR with key
        printf("%016lx\n", plaintext_block);
    }
}

// Function to encrypt plaintext using CBC mode
void CBC_encrypt(uint64_t plaintext[], uint64_t key[], uint64_t iv, int num_blocks) {
    printf("Plaintext blocks:\n");
    print_blocks(plaintext, num_blocks);

    // Encryption process (simplified)
    printf("Encrypting using CBC mode...\n");
    printf("Ciphertext blocks:\n");
    uint64_t prev_ciphertext_block = iv; // Initialization vector
    // Perform encryption of each block using the previous ciphertext block
    int i;
    for (i = 0; i < num_blocks; i++) {
        // Simplified encryption process (just XOR with key and previous ciphertext block for demonstration)
        uint64_t ciphertext_block = plaintext[i] ^ key[0] ^ prev_ciphertext_block; // Example: XOR with key and previous ciphertext block
        printf("%016lx\n", ciphertext_block);
        prev_ciphertext_block = ciphertext_block; // Update previous ciphertext block for chaining
    }
}

// Function to decrypt ciphertext using CBC mode
void CBC_decrypt(uint64_t ciphertext[], uint64_t key[], uint64_t iv, int num_blocks) {
    printf("Ciphertext blocks:\n");
    print_blocks(ciphertext, num_blocks);

    // Decryption process (simplified)
    printf("Decrypting using CBC mode...\n");
    printf("Decrypted plaintext blocks:\n");
    uint64_t prev_ciphertext_block = iv; // Initialization vector
    // Perform decryption of each block using the previous ciphertext block
    int i;
    for (i = 0; i < num_blocks; i++) {
        // Simplified decryption process (just XOR with key and previous ciphertext block for demonstration)
        uint64_t plaintext_block = ciphertext[i] ^ key[0] ^ prev_ciphertext_block; // Example: XOR with key and previous ciphertext block
        printf("%016lx\n", plaintext_block);
        prev_ciphertext_block = ciphertext[i]; // Update previous ciphertext block for chaining
    }
}

// Function to print blocks
void print_blocks(uint64_t blocks[], int num_blocks) {
    int i;
    for (i = 0; i < num_blocks; i++) {
        printf("%016lx\n", blocks[i]);
    }
    printf("\n");
}

