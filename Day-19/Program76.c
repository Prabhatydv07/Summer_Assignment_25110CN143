#include<stdio.h>

int main(){

    int r,c;
    printf("Enter the no of rows and columns ");
    scanf("%d %d", &r,&c);

    int arr[r][c];

    printf("Enter the elemns of matrix1: \n");
    for(int i = 0; i<r; i++){
        for(int j = 0; j<c; j++){
            scanf("%d", &arr[i][j]);
        }
    }

    int sum = 0;

    for(int i=0; i<r;i++){
        for(int j =0; j<c; j++){
            if(i == j) sum+= arr[i][j];
        }
    }

    printf("The sum of diagonal elements is : %d", sum);

    return 0;
}