#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of rows for number pyramid : ");
    scanf("%d", &n);

    for(int i = 1; i<=n; i++){
        for(int j = 1;j<=n-i;j++){//print spaces
            printf("  ");
        }

        for(int j = 1; j <= i; j++){ //count from a to n
            printf("%c ", (char)(64+j));
        }

        for(int k = i-1; k >= 1; k--){ //count down from n to a 
            printf("%c ", (char)(64+k));
        }
        printf("\n");
    }
    return 0;
}