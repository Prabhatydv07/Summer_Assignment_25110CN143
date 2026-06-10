#include<stdio.h>

int main(){
    int n;
    printf("Enter the numbe of rows for star pyramid patter : ");
    scanf("%d", &n);

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<i; j++){//for printing spaces
            printf("  ");
        }
        for(int k = 2*n-2*i+1; k>0;k--){ //for decreasing star
            printf("* ");
        }
        printf("\n");//for printing in new line
    }
    return 0;
}