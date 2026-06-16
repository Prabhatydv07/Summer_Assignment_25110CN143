#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);

    printf("Enter the elements of the array - \n");
    int arr[n];
    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int actsum = ((n+1) * (n+2)) / 2;
    int arrsum = 0;
    for(int i = 0; i<n; i++){
        arrsum += arr[i];
    }

    printf("The missing element in the array is : %d", actsum-arrsum);
    return 0;
}