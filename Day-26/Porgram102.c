#include<stdio.h>

int main(){
    int n;
    printf("Enter your age :");
    scanf("%d", &n);

    if(n>=18) printf("You are eligible for vote");
    else printf("You are not eligible for vote");

    return 0;
}