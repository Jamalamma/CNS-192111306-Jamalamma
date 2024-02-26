#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to count the frequency of each letter in the ciphertext
void calculateFrequency(char ciphertext[], int frequency[]) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[toupper(ciphertext[i]) - 'A']++;
        }
    }
}

// Function to perform a simple letter frequency attack
void frequencyAttack(char ciphertext[]) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);

    // Sort frequencies and find the most likely letters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int maxIndex = 0;

        // Find the letter with the highest frequency
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > frequency[maxIndex]) {
                maxIndex = j;
            }
        }

        // Print the most likely plaintext letters
        printf("Possible plaintext for letter %c: %c\n", 'A' + maxIndex, 'E' - ('A' + maxIndex) + 'A');

        // Set the frequency to -1 to avoid printing the same letter again
        frequency[maxIndex] = -1;
    }
}

int main() {
    char ciphertext[1000];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("\nTop 10 possible plaintexts:\n");
    frequencyAttack(ciphertext);

    return 0;
}
