#include<stdio.h>

int fact(int n){
    int prod = 1;
    for (int i = 1; i<=n; i++){
        prod *= i;
    }
    return prod;
}

int main(){
    int n, dig, sum = 0;
    printf("Enter the value of n to check strong number : ");
    scanf("%d", &n);

    int temp = n;

    while(temp != 0){
        dig = temp % 10;
        sum += fact(dig);
        temp /= 10;
    }

    if(sum == n){
        printf("The number %d is a strong number", n);
    }

    else{
        printf("The entered number is not a strong number ");
    }

    
    return 0;
}