#include<stdio.h>

int main(){
    int n, temp,cpy,rev = 0; 
    printf("Enter the number to find palindrome :" );
    scanf("%d", &n);
    cpy = n;

    while(n != 0){
        temp = n % 10;
        rev = rev * 10 + temp ;
        n /= 10;
    }

    if( cpy = rev){
        printf("The entered number is a palindrome ");
    }

    else{
        printf("The entered number is not palindrome ");
    }
    return 0;
}