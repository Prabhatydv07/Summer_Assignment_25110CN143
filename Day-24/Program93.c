#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isRotation(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // Must be same length and non-empty
    if (len1 != len2 || len1 == 0)
        return 0;

    // Concatenate s1 with itself
    char *doubled = malloc(2 * len1 + 1);
    strcpy(doubled, s1);
    strcat(doubled, s1);

    // Check if s2 is a substring of s1+s1
    int result = strstr(doubled, s2) != NULL;
    free(doubled);
    return result;
}

int main() {
    char s1[100], s2[100];

    printf("Enter string 1: ");
    scanf("%99s", s1);
    printf("Enter string 2: ");
    scanf("%99s", s2);

    if (isRotation(s1, s2))
        printf("\"%s\" IS a rotation of \"%s\"\n", s2, s1);
    else
        printf("\"%s\" is NOT a rotation of \"%s\"\n", s2, s1);

    return 0;
}