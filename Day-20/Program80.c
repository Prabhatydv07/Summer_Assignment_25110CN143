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


    int ccount = 0;

    while(ccount<c){
        int sum = 0;
        for(int i = 0; i<c; i++){
            sum += arr[i][ccount];
        }
        ccount++;
        printf("The column %d sum is : %d\n",ccount,sum);

    }
    return 0;
}