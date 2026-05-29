#include<stdio.h>

int main(){
    int n, temp,cpy,rev = 0; 
    printf("Enter the number to find the sum of digits :" );
    scanf("%d", &n);
    cpy = n;

    while(n != 0){
        temp = n % 10;
        rev = rev * 10 + temp ;
        n /= 10;
    }

    printf("The reverse of number  %d is : %d", cpy, rev);
    return 0;
}