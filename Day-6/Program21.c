#include <stdio.h>

void decToBinary(int n) {
    if (n == 0) {
        printf("0");
        return;
    }

    int binary[32];
    int i = 0;

    while (n > 0) {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }

    // Print in reverse order (MSB to LSB)
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
}

int main() {
    int num;

    printf("Enter a decimal number: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    printf("Decimal: %d\n", num);
    printf("Binary:  ");
    decToBinary(num);
    printf("\n");

    return 0;
}