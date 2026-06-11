#include<stdio.h>

long long fact(int a){
    int long long f = 1;
    for(int i = 1; i<=a;i++){
        f *= i;
    }
    return f;
}

int main(){
    int a;
    printf("Enter the number to check prime :");
    scanf("%d",&a);


    printf("The factorial of %d is : %lld", a, fact(a));
    return 0;
}