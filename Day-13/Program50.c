#include<stdio.h>

int main(){
    int n, sum = 0, avg =0;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter array elements : ");
    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i<n ; i++){
        sum += arr[i];
    }

    avg = sum/n;

    printf("The sum of the array is : %d\n", sum);
    printf("The average of array is : %d", avg);
    return 0;
}