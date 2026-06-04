#include<stdio.h>


int fibonaic(int n){
    if(n<=0) return 0;
    if(n == 1) return 1;

    int a = 0, b=1, fib = 0;
    for(int i = 2; i<=n; i++){
        fib = a + b;
        a = b;
        b = fib;
    }
    return fib;
}

int main(){
    int n;
    printf("Enter the value of n for fibonaci series : ");
    scanf("%d", &n);

    printf("The %d element of the fibonaci series is : %d", n, fibonaic(n));
    return 0;
}