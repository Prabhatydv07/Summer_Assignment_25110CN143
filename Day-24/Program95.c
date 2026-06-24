#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Extracts words one by one from str (starting at *pos),
   writing each into word[]. Returns word length, or 0 at end. */
int nextWord(const char *str, int *pos, char *word) {
    int len = strlen(str);

    // Skip non-alphabetic characters (spaces, punctuation)
    while (*pos < len && !isalpha(str[*pos]))
        (*pos)++;

    if (*pos >= len) return 0;  // no more words

    int start = *pos;
    while (*pos < len && isalpha(str[*pos]))
        (*pos)++;

    int wordLen = *pos - start;
    strncpy(word, str + start, wordLen);
    word[wordLen] = '\0';
    return wordLen;
}

void findLongestWord(const char *sentence) {
    char word[200];
    char longest[200] = "";
    int maxLen = 0;
    int pos = 0;
    int wordCount = 0;

    while (1) {
        int len = nextWord(sentence, &pos, word);
        if (len == 0) break;

        wordCount++;
        printf("  Word %2d: %-20s (length %d)\n", wordCount, word, len);

        if (len > maxLen) {
            maxLen = len;
            strcpy(longest, word);
        }
    }

    if (wordCount == 0) {
        printf("  No words found in the input.\n");
    } else {
        printf("\nTotal words : %d\n", wordCount);
        printf("Longest word: \"%s\" (length %d)\n", longest, maxLen);
    }
}

int main() {
    char sentence[1000];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';

    printf("\nScanning words:\n");
    findLongestWord(sentence);

    return 0;
}