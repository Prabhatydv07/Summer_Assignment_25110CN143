#include<stdio.h>

int main(){
    int r,c;
    printf("Enter the no of rows and columns ");
    scanf("%d %d", &r,&c);

    int arr[r][c];

    printf("Enter the elemns of array1: \n");
    for(int i = 0; i<r; i++){
        for(int j = 0; j<c; j++){
            scanf("%d", &arr[i][j]);
        }
    }

    int r1,c1;
    printf("E1nter the no of rows and columns of second array: ");
    scanf("%d %d", &r1,&c1);

    if(r != r1 || c != c1){
        printf("Enter valid no of rows and columns");
        return 0;
    }

    int arr1[r1][c1];

    printf("Enter the elemts of array2: \n");
    for(int i = 0; i<r1; i++){
        for(int j = 0; j<c1; j++){
            scanf("%d", &arr1[i][j]);
        }
    }

    int arr2[r1][c1];

    for(int i = 0; i<r1; i++){
        for(int j = 0; j<c1; j++){
            arr2[i][j] = arr[i][j] + arr1[i][j];
        }
    }

    printf("The union of both the arrays are :\n ");

    for(int i = 0; i<r1; i++){
        for(int j = 0; j<c1; j++){
            printf("%d ", arr2[i][j]);
        }
        printf("\n");
    }
    return 0;
}