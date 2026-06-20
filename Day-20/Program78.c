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

    printf("Original marix is : ");
    for(int i=0;i<r;i++){
        for(int j = 0; j<c;j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


    int arr1[c][r];
    for(int i = 0; i<r;i++){
        for(int j = 0; j<c; j++){
            arr1[j][i]= arr[i][j];
        }
    }

    int flag = 1;

    for(int i = 0; i<c; i++){
        for(int j = 0; j<r; j++){
            if(arr[i][j] != arr1[i][j]){
                flag = 0;
            }
        }
    }

    if(flag){
        printf("The matrix is symmetric ");
    }

    else{
        printf("The matrix is not symmetric");
    }

    return 0;
}