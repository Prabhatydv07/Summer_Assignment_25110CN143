#include <stdio.h>
#include <stdlib.h>

int* mergeSortedArrays(int* a, int aLen, int* b, int bLen, int* resultLen) {
    *resultLen = aLen + bLen;
    int* result = (int*)malloc(*resultLen * sizeof(int));
    if (!result) return NULL;

    int i = 0, j = 0, k = 0;

    while (i < aLen && j < bLen) {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < aLen) result[k++] = a[i++];
    while (j < bLen) result[k++] = b[j++];

    return result;
}

int main() {
    int a[] = {1, 3, 5, 7, 9};
    int b[] = {2, 4, 6, 8, 10};
    int aLen = sizeof(a) / sizeof(a[0]);
    int bLen = sizeof(b) / sizeof(b[0]);
    int resultLen;

    int* merged = mergeSortedArrays(a, aLen, b, bLen, &resultLen);
    if (!merged) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Array A:  ");
    for (int i = 0; i < aLen; i++) printf("%d ", a[i]);

    printf("\nArray B:  ");
    for (int i = 0; i < bLen; i++) printf("%d ", b[i]);

    printf("\nMerged:   ");
    for (int i = 0; i < resultLen; i++) printf("%d ", merged[i]);
    printf("\n");

    free(merged);
    return 0;
}