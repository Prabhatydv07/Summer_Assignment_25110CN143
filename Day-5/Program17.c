#include<stdio.h>

int main(){
    int n, sum = 0; 
    printf("Enter the value of n for the number : ");
    scanf("%d", &n);

    for(int i = 1; i<n; i++){
        if(n%i == 0){
            sum += i;
        }
    }

    if(sum == n){
        printf("The number is perfect ");
    }

    else{
        printf("The number is not perfect ");
    }

    return 0;
}