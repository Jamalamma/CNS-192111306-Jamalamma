#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 8 // Block size in bytes (64 bits)

// Function to perform left shift on a block
void left_shift(unsigned char *block) {
    unsigned char carry = 0;
    int i; // Move the declaration outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        unsigned char temp = block[i] >> 7; // Get the MSB (most significant bit)
        block[i] = (block[i] << 1) | carry; // Left shift and append the carry
        carry = temp; // Update carry with the previous MSB
    }
    if (carry) {
        // If the leftmost bit of the last byte was 1, perform a bitwise XOR with a constant
        block[BLOCK_SIZE - 1] ^= 0x87; // Constant for 64-bit block size
    }
}

// Function to generate CMAC subkeys
void generate_subkeys(unsigned char *key, unsigned char *subkey1, unsigned char *subkey2) {
    unsigned char zero_block[BLOCK_SIZE] = {0}; // Block of all 0 bits

    // Generate the first subkey
    encrypt_block(zero_block, key, subkey1);
    left_shift(subkey1);

    // Generate the second subkey
    unsigned char temp[BLOCK_SIZE];
    int i; // Move the declaration outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = subkey1[i];
    }
    left_shift(subkey1);
    if ((temp[0] & 0x80) == 0x80) {
        temp[BLOCK_SIZE - 1] ^= 0x1B; // Constant for 64-bit block size
    }
    for (i = 0; i < BLOCK_SIZE; i++) {
        subkey2[i] = temp[i];
    }
}

// Function to encrypt a block using a block cipher (for demonstration purposes)
void encrypt_block(unsigned char *block, unsigned char *key, unsigned char *output) {
    // This is a placeholder for actual block cipher encryption
    // In a real implementation, a proper block cipher (e.g., AES) should be used
    int i; // Move the declaration outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i]; // Dummy encryption: XOR with key
    }
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6}; // Example key
    unsigned char subkey1[BLOCK_SIZE];
    unsigned char subkey2[BLOCK_SIZE];

    // Generate CMAC subkeys
    generate_subkeys(key, subkey1, subkey2);

    // Print the subkeys
    printf("Subkey 1: ");
    int i; // Move the declaration outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", subkey2[i]);
    }
    printf("\n");

    return 0;
}

