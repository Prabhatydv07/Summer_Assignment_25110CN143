#include<stdio.h>

int power(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }
    return result;
}

int main(){
    int n, pow = 0;
    printf("Enter the value of n : ");
    scanf("%d", &n);

    printf("Enter the value of raised to the power : ");
    scanf("%d", & pow);

    int result = power(n,pow);

    printf("%d Raised to the power %d is : %d", n, pow, result);
    return 0;
}