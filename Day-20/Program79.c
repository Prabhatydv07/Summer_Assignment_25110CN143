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

    printf("Original marix is \n: ");
    for(int i=0;i<r;i++){
        for(int j = 0; j<c;j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }


    int rcount = 0;

    while(rcount<r){
        int sum = 0;
        for(int i = 0; i<c; i++){
            sum += arr[rcount][i];
        }
        rcount++;
        printf("The row %d sum is : %d\n", rcount,sum);

    }
    return 0;
}