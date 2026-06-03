#include<stdio.h>

int main(){
    int n;
    printf("Enter the number to check whether it is even or not :");
    scanf("%d", &n);

    if(n % 2 == 0){
        printf("%d is an even number", n);
    }

    else{
        printf("%d is an odd number ", n);
    }
    return 0;
}