#include<stdio.h>

int fibonaci(int n){
    if(n == 0) return 0;
    else if(n==1) return 1;
    else return(fibonaci(n-1)+fibonaci(n-2));
}
int main(){
    int n;
    printf("Enter the value of n for fibonaci series : ");
    scanf("%d", &n);

    for(int i = 0; i<=n ; i++){
        printf("%d ", fibonaci(i));
    }
    return 0;
}