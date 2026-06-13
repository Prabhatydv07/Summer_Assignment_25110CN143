#include<stdio.h>

int main(){
    int n, max, min;
    printf("Enter the length of array : ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array \n");

    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int nodd= 0 ,neven = 0;
    
    for(int i = 0; i<n; i++){
        if(arr[i]%2== 0) neven++;
        else nodd++;
    }

    printf("The number of even elements are : %d", neven);
    printf("The number of odd elements are : %d", nodd);


    return 0;
}