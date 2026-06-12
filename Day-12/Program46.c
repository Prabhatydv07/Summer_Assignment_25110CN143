#include<stdio.h>

/* Returns 1 if n is an Armstrong number, else 0 */
int isArmstrong(int n) {
    int temp, digits = 0, sum = 0, cpy = n;

    /* Step 1: Count number of digits */
    temp = n;
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    /* Step 2: Sum each digit raised to power 'digits' */
    while (cpy != 0) {
        temp = cpy % 10;
        int power = 1;
        for (int i = 0; i < digits; i++)
            power *= temp;
        sum += power;
        cpy /= 10;
    }

    return (sum == n);
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