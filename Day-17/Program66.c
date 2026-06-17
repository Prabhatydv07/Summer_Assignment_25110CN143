#include <stdio.h>

int isPresent(int arr[], int size, int element) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) return 1;
    }
    return 0;
}

void unionArrays(int a[], int m, int b[], int n) {
    int result[m + n];
    int k = 0;

    // Add all elements of a[]
    for (int i = 0; i < m; i++) {
        if (!isPresent(result, k, a[i]))
            result[k++] = a[i];
    }

    // Add elements of b[] not already in result
    for (int i = 0; i < n; i++) {
        if (!isPresent(result, k, b[i]))
            result[k++] = b[i];
    }

    printf("Union: { ");
    for (int i = 0; i < k; i++)
        printf("%d ", result[i]);
    printf("}\n");
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {3, 4, 5, 6, 7};
    int m = sizeof(a) / sizeof(a[0]);
    int n = sizeof(b) / sizeof(b[0]);

    printf("Array A: { ");
    for (int i = 0; i < m; i++) printf("%d ", a[i]);
    printf("}\n");

    printf("Array B: { ");
    for (int i = 0; i < n; i++) printf("%d ", b[i]);
    printf("}\n");

    unionArrays(a, m, b, n);
    return 0;
}