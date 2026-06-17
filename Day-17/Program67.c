#include<stdio.h>

int main(){
    int n1;
    printf("Enter the number of rows of array 1 (should be greater than or equal to array 2):");
    scanf("%d", &n1);
    
    int c1;
    printf("Enter the number of columns of array 1 (should be greater than or equal to array 2) :");
    scanf("%d", &c1);
    int arr1[n1][c1];

    //taking first array as input 
    printf("Enter the elemts of array1: \n");
    for(int i = 0; i<n1; i++){
        for(int j = 0; j<c1; j++){
            scanf("%d", &arr1[i][j]);
        }
    }

    int n2;
    printf("Enter the number of rows of array 2 :");
    scanf("%d", &n2);

    int c2;
    printf("Enter the number of columns of array 2 :");
    scanf("%d", &c2);
    int arr2[n2][c2];

    //taking second array as input
    printf("Enter the elemts of array2: \n");
    for(int i = 0; i<n2; i++){
        for(int j = 0; j<c2; j++){
            scanf("%d", &arr2[i][j]);
        }
    }

    int arr3[100][100];

    //storing common elemnts in arr3
    for(int i = 0; i<n1;i++){
        for(int j = 0; j<c1; j++){
            if(arr1[i][j] == arr2[i][j]){
                arr3[i][j] = arr1[i][j];
            }
        }
    }

    printf("The elements common in both the array are : ");

    for(int i =0 ;i<n1; i++){
        for(int j = 0; j<c1; j++){
            printf("%d ", arr3[i][j]);
        }
        printf("\n");
    }
    return 0;
}