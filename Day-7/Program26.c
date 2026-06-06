#include<stdio.h>

int fibonaci(int n){
    if(n == 1) return 1;
    if(n == 0) return 0;
    else{
        return(fibonaci(n-1) + fibonaci(n-2));
    }
}

int main(){
    int n ;
    printf("Enter the number : ");
    scanf("%d", &n);

    printf("Fibonaci Serires is : ");

    for(int i = 0; i<n; i++){
        printf("%d ", fibonaci(i));
    }


    return 0;
}