#include<stdio.h>

int main(){
    int n, temp,cpy,prod = 1; 
    printf("Enter the number to find product of digits :" );
    scanf("%d", &n);
    cpy = n;

    while(n != 0){
        temp = n % 10;
        prod *= temp;
        n/=10;
    }

    printf("The product of digits in   %d is : %d", cpy, prod);
    return 0;
}