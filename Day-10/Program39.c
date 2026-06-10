#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of rows for number pyramid : ");
    scanf("%d", &n);

    for(int i = 1; i<=n; i++){
        for(int j = 1;j<=n-i;j++){//print spaces
            printf("  ");
        }

        for(int j = 1; j <= i; j++){ //count from 1 to i
            printf("%d ", j);
        }

        for(int k = i-1; k >= 1; k--){ //count down from i - 1 to 1
            printf("%d ", k);
        }
        printf("\n");
    }
    return 0;
}