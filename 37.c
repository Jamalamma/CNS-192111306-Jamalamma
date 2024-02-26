#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies in the given text
void calculateFrequencies(char *text, int *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequencies[letter - 'a']++;
        }
    }
}

// Function to decrypt text using a given key
void decryptText(char *ciphertext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = tolower(ciphertext[i]);
            ciphertext[i] = isupper(ciphertext[i]) ? toupper(key[letter - 'a']) : tolower(key[letter - 'a']);
        }
    }
}

// Function to score the fitness of the decrypted text based on letter frequencies
int calculateFitness(int *frequencies) {
    int fitness = 0;
    // Assuming English letter frequencies
    char englishFrequencies[] = "etaoinshrdlcumwfgypbvkjxqz";
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        fitness += frequencies[i] * (ALPHABET_SIZE - englishFrequencies[i] + 1);
    }

    return fitness;
}

// Function to perform letter frequency attack
void letterFrequencyAttack(char *ciphertext, int topPlaintexts) {
    int frequencies[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, frequencies);

    char key[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'a' + i;
    }

    // Sort key based on frequencies
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequencies[j] > frequencies[i]) {
                int tempFreq = frequencies[i];
                frequencies[i] = frequencies[j];
                frequencies[j] = tempFreq;

                char tempKey = key[i];
                key[i] = key[j];
                key[j] = tempKey;
            }
        }
    }

    printf("Possible plaintexts:\n");
    for (int i = 0; i < topPlaintexts; i++) {
        decryptText(ciphertext, key);
        int fitness = calculateFitness(frequencies);
        printf("Plaintext #%d (Fitness Score: %d): %s\n", i + 1, fitness, ciphertext);
    }
}

int main() {
    char ciphertext[1000];
    int topPlaintexts;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter the number of top plaintexts to display: ");
    scanf("%d", &topPlaintexts);

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}
