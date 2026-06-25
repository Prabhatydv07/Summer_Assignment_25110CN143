#include <stdio.h>
#include <string.h>

#define CHAR_SIZE 26

void findCommonChars(char* strings[], int n) {
    // Count min frequency of each character across all strings
    int minFreq[CHAR_SIZE] = {0};

    // Initialize with frequency from first string
    for (int c = 0; c < CHAR_SIZE; c++) {
        for (int i = 0; i < (int)strlen(strings[0]); i++)
            if (strings[0][i] - 'a' == c) minFreq[c]++;
    }

    // For each remaining string, take the minimum frequency
    for (int s = 1; s < n; s++) {
        int freq[CHAR_SIZE] = {0};
        for (int i = 0; i < (int)strlen(strings[s]); i++)
            freq[strings[s][i] - 'a']++;

        for (int c = 0; c < CHAR_SIZE; c++)
            if (freq[c] < minFreq[c]) minFreq[c] = freq[c];
    }

    // Print common characters
    printf("Common characters: ");
    int found = 0;
    for (int c = 0; c < CHAR_SIZE; c++) {
        for (int k = 0; k < minFreq[c]; k++) {
            printf("%c ", 'a' + c);
            found++;
        }
    }
    if (!found) printf("(none)");
    printf("\n");
}

int main() {
    char* strings[] = {"bella", "label", "roller"};
    int n = sizeof(strings) / sizeof(strings[0]);

    printf("Strings: ");
    for (int i = 0; i < n; i++) printf("\"%s\" ", strings[i]);
    printf("\n");

    findCommonChars(strings, n);

    // Second test
    char* strings2[] = {"cool", "lock", "cook"};
    int n2 = sizeof(strings2) / sizeof(strings2[0]);

    printf("\nStrings: ");
    for (int i = 0; i < n2; i++) printf("\"%s\" ", strings2[i]);
    printf("\n");

    findCommonChars(strings2, n2);

    return 0;
}