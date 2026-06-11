#include<stdio.h>

int isprime(int a){
    for(int i = 2; i<a; i++){
        if(a%i == 0){
            break;
        }
        else return 1;
    }
}

int main(){
    int a;
    printf("Enter the number to check prime :");
    scanf("%d",&a);

    if(isprime(a)){
        printf("%d is a prime number ", a);
    }
    else{
        printf("The eneterd number is not prime");
    }
    return 0;
}