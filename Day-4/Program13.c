#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of terms in fibonaci series : ");
    scanf("%d", &n);

    int a = 0, b =1 , fib = 0;

    printf("%d ", a);
    printf("%d ", b);

    for(int i = 2; i<n; i++){
        fib = a + b;
        a = b;
        b = fib;
        printf("%d ", fib);
    }

    
    return 0;
}