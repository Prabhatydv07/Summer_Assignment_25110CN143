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

    int r1,c1;
    printf("Enter the no of rows and columns ");
    scanf("%d %d", &r1,&c1);

    int arr1[r1][c1];

    printf("Enter the elemns of matrix2: \n");
    for(int i = 0; i<r1; i++){
        for(int j = 0; j<c1; j++){
            scanf("%d", &arr1[i][j]);
        }
    }

    if(r != r1 || c != c1){
        printf("Enter valid order of matrix");
    }

    int arr2[r][c];

    
    for(int i = 0; i<r;i++){
        for(int j  = 0; j<c; j++){
            arr2[i][j] = arr[i][j] - arr1[i][j];
        }
    }


    printf("The subtracted matrix is : ");


    for(int i = 0; i<r; i++){
        for(int j = 0; j<c; j++){
            printf("%d ", arr2[i][j]);
        }
        printf("\n");
    }

    return 0;
}