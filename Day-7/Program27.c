#include<stdio.h>

int sumdig(int n){
    if(n < 0) n = -n; //for handling negative numbers
    if(n == 0) return 0; //base case
    return (n%10) + sumdig(n/10); //recursive case
}

int main(){
    int n;
    printf("Enter the number : ");
    scanf("%d", &n);
    
    printf("Sum of digits is : %d", sumdig(n));

    
    return 0;
}