#include<stdio.h>

int sum(int a, int b){ //program to calculate the sum
    return (a+b);
}

int main(){
    int a, b;
    printf("Enter the two numbers :");
    scanf("%d %d", &a,&b);

    int s = sum(a,b);
    printf("The sum of %d and %d is : %d", a,b,s);
    return 0;
}