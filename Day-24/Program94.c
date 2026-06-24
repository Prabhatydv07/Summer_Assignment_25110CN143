#include <stdio.h>
#include <string.h>

/* Compress: write compressed result into 'out', return compressed length.
   If compression makes it longer, returns -1. */
int compress(const char *in, char *out) {
    int i = 0, j = 0;
    int len = strlen(in);

    while (i < len) {
        char current = in[i];
        int count = 1;

        // Count consecutive occurrences of current char
        while (i + count < len && in[i + count] == current)
            count++;

        // Write char; write count only if > 1
        out[j++] = current;
        if (count > 1)
            j += sprintf(&out[j], "%d", count);

        i += count;
    }
    out[j] = '\0';

    return (j < len) ? j : -1;   // -1 = no benefit
}

/* Decompress: expand RLE string back to original */
void decompress(const char *in, char *out) {
    int i = 0, j = 0;
    int len = strlen(in);

    while (i < len) {
        char ch = in[i++];
        int count = 0;

        // Read optional digit(s) after the character
        while (i < len && in[i] >= '0' && in[i] <= '9')
            count = count * 10 + (in[i++] - '0');

        if (count == 0) count = 1;   // no number → appears once

        for (int k = 0; k < count; k++)
            out[j++] = ch;
    }
    out[j] = '\0';
}

int main() {
    char input[500], compressed[1000], decompressed[500];

    printf("Enter string to compress: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';   // strip newline

    int result = compress(input, compressed);

    if (result == -1) {
        printf("Compressed : %s  (no size benefit — kept original)\n", compressed);
    } else {
        printf("Original   : %s  (%zu chars)\n", input, strlen(input));
        printf("Compressed : %s  (%d chars)\n", compressed, result);
        printf("Ratio      : %.1f%%\n", 100.0 * result / strlen(input));
    }

    decompress(compressed, decompressed);
    printf("Decompressed: %s\n", decompressed);

    return 0;
}