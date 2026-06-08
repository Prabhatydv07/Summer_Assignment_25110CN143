#include<stdio.h>

int main(){
    int n;
    printf("Enter the no of rows : ");
    scanf("%d", &n);

    int count = 1; //external variable for initialize count

    for(int i = 0; i<n; i++){
        for(int j = 0; j<=i; j++){
            printf("%d ", count);
        }
        count++;
        printf("\n");
    }
    return 0;
}