#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Sort by length; alphabetical order as tiebreaker
int compare(const void* a, const void* b) {
    const char* sa = *(const char**)a;
    const char* sb = *(const char**)b;
    int lenDiff = (int)strlen(sa) - (int)strlen(sb);
    return lenDiff != 0 ? lenDiff : strcmp(sa, sb);
}

void printWords(char* words[], int n) {
    for (int i = 0; i < n; i++)
        printf("  %2d. %-15s (%zu letters)\n", i + 1, words[i], strlen(words[i]));
}

int main() {
    char* words[] = {
        "banana", "kiwi", "strawberry", "fig", "apple",
        "mango", "blueberry", "plum", "grape", "pear"
    };
    int n = sizeof(words) / sizeof(words[0]);

    printf("Before sorting:\n");
    printWords(words, n);

    qsort(words, n, sizeof(char*), compare);

    printf("\nAfter sorting (shortest to longest):\n");
    printWords(words, n);

    return 0;
}