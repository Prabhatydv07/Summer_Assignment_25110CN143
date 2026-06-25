#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAMES 100
#define MAX_LEN   100

// Comparator for qsort
int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void sortNames(char* names[], int n) {
    qsort(names, n, sizeof(char*), compare);
}

void printNames(char* names[], int n) {
    for (int i = 0; i < n; i++)
        printf("  %2d. %s\n", i + 1, names[i]);
}

int main() {
    char* names[] = {
        "Charlie", "Alice", "Eve", "Bob", "Diana",
        "Frank", "Ivy", "Grace", "Henry", "Jack"
    };
    int n = sizeof(names) / sizeof(names[0]);

    printf("Before sorting:\n");
    printNames(names, n);

    sortNames(names, n);

    printf("\nAfter sorting (alphabetical):\n");
    printNames(names, n);

    return 0;
}