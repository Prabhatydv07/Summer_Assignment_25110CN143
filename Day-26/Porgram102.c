#include<stdio.h>

int main(){
    int n ;
    printf("Enter you age : ");
    scanf("%d", &n);

    if(n>=18) printf("You are eligible to vote");
    else printf("You are not eligible to vote");
}