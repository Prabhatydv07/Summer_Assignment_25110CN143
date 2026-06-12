#include<stdio.h>

int ispalindrome(int n){
    int temp,cpy,rev = 0;
    cpy = n; //to create the copy of the number 
    while(n!=0){
        temp = n%10;
        rev = rev * 10 + temp; //calculating the reverese of number 
        n/= 10;
    }
    if(cpy == rev) return 1 ;
    else return 0;
}
int main(){
    int n;
    printf("Enter the number ");
    scanf("%d", &n);

    if (ispalindrome(n)){
        printf("The entered number is palindrome ");
    }

    else{
        printf("The enterd number is not palindrome");
    }
    return 0;
}