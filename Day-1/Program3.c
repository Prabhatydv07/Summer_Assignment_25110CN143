#include<stdio.h>

int main(){
    int n, fact = 1;
    printf("Enter the number to find factorial  :" );
    scanf("%d", &n);

    for(int i = 1; i<=n; i++){
        fact *= i;
    }

    printf("Factorial is %d", fact);
    return 0;
}