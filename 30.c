#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 16

void xor_blocks(unsigned char *block1, unsigned char *block2, unsigned char *result) {
    int i;
    for (i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

int main() {
	int i;
    unsigned char block1[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                                         0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    unsigned char block2[BLOCK_SIZE] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                         0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
    unsigned char result[BLOCK_SIZE];

    xor_blocks(block1, block2, result);

    printf("Result: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", result[i]);
    }
    printf("\n");

    return 0;
}

