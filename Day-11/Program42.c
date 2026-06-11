#include<stdio.h>

int max(int a, int b){ //program to calculate the sum
    if(a>=b){
        return a;
    }
    else{
        return b;
    }
}

int main(){
    int a, b;
    printf("Enter the two numbers :");
    scanf("%d %d", &a,&b);

    int m = max(a,b);
    printf("The maximum of %d and %d is : %d", a,b,m);
    return 0;
}