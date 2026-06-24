#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Remove duplicate characters from str, result written into out.
   Preserves original order; first occurrence of each char is kept.
   Case-sensitive by default; pass caseSensitive=0 to ignore case. */
void removeDuplicates(const char *str, char *out, int caseSensitive) {
    int seen[256] = {0};   // one slot per ASCII character
    int j = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char ch = str[i];
        unsigned char key = caseSensitive ? ch : tolower(ch);

        if (!seen[key]) {
            seen[key] = 1;
            out[j++] = ch;   // keep original case in output
        }
        // else: duplicate — skip it
    }
    out[j] = '\0';
}

void printReport(const char *original, const char *result) {
    int removed = strlen(original) - strlen(result);
    printf("\nOriginal  : \"%s\"  (%zu chars)\n", original, strlen(original));
    printf("Result    : \"%s\"  (%zu chars)\n", result, strlen(result));
    printf("Removed   : %d duplicate(s)\n", removed);
}

int main() {
    char input[500], output[500];
    int choice;

    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Case-sensitive? (1 = yes, 0 = no): ");
    scanf("%d", &choice);

    removeDuplicates(input, output, choice);
    printReport(input, output);

    return 0;
}