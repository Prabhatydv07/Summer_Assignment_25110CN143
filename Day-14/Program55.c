#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i<n;i++){
        scanf("%d", &arr[i]);
    }

    int max = arr[0] , smax = arr[0];
    for(int i = 0; i<n; i++){
        if(arr[i]>max) max = arr[i];
    }

    for(int i = 0; i<n; i++){
        if(arr[i]>smax && arr[i]<max) smax = arr[i];
    }

    printf("The second largest element of the array is : %d", smax);
    return 0;
}