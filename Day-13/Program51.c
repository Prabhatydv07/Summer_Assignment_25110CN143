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

    max = min = arr[0];

    for(int i = 1; i<n; i++){
        if(arr[i]>max) max = arr[i];
        if(arr[i]<min) min = arr[i];
    }

    printf("The maximum element of the array is : %d\n", max);
    printf("The minimum element of the array is : %d", min);


    return 0;
}