#include <stdio.h>
#include <math.h>

int isArmstrong(int n) {
    int original = n, sum = 0, digits = 0, temp = n;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = n;
    while (temp != 0) {
        int d = temp % 10;
        sum += pow(d, digits);
        temp /= 10;
    }

    return sum == original;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (isArmstrong(n))
        printf("%d is an Armstrong number\n", n);
    else
        printf("%d is not an Armstrong number\n", n);

    return 0;
}