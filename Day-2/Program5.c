#include<stdio.h>

int main(){
    int n, temp,cpy,sum = 0; 
    printf("Enter the number to find the sum of digits :" );
    scanf("%d", &n);
    cpy = n;

    while(n != 0){
        temp = n % 10;
        sum += temp;
        n /= 10;
    }

    printf("The sum of digits in %d is : %d", cpy, sum);
    return 0;
}