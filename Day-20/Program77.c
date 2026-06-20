#include<stdio.h>

int main(){
    int r,c;
    printf("Enter the no of rows and columns ");
    scanf("%d %d", &r,&c);

    int arr[r][c];
    printf("Enter the elements of matrix1: \n");
    for(int i = 0; i<r; i++)
        for(int j = 0; j<c; j++)
            scanf("%d", &arr[i][j]);

    int r1,c1;
    printf("Enter the no of rows and columns ");
    scanf("%d %d", &r1,&c1);

    int arr1[r1][c1];
    printf("Enter the elements of matrix2: \n");
    for(int i = 0; i<r1; i++)
        for(int j = 0; j<c1; j++)
            scanf("%d", &arr1[i][j]);

    int arr2[r][c1];

    if(c != r1){
        printf("Enter valid order of matrix");
    }
    else{
        // initialize arr2 to 0
        for(int i = 0; i<r; i++)
            for(int j = 0; j<c1; j++)
                arr2[i][j] = 0;

        for(int i = 0; i<r; i++){
            for(int j = 0; j<c1; j++){
                for(int k = 0; k<c; k++){
                    arr2[i][j] += arr[i][k] * arr1[k][j];
                }
            }
        }

        printf("The multiplied matrix is : \n");
        for(int i = 0; i<r; i++){
            for(int j = 0; j<c1; j++){
                printf("%d ", arr2[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}