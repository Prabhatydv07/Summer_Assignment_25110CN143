#include<stdio.h>

int isperfect(int n){
    int sum = 0;
    for(int i = 1; i<n; i++){
        if(n%i == 0) sum+= i;
    }
    if(sum == n) return 1;
    else return 0;
}

int main(){
    int n;
    printf("Enter the number : ");
    scanf("%d", &n);

    if(isperfect(n)){
        printf("The entered number is a perfect number ");
    }

    else{
        printf("%d is not a perfect number", n);
    }
    return 0;
}