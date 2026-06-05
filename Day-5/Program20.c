#include<stdio.h>

int main(){
    int n, fact = 0;
    printf("Enter the value of number :");
    scanf("%d", &n);

    for(int i = 2; i<n; i++){
        if(n%i == 0){
            fact = i;
        }
    }

    printf("Largest prime factor is : %d", fact);
    return 0;
}