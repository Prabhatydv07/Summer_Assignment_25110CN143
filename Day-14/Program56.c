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

    int temp = 0;
    for(int i = 0; i<n; i++){
        temp = arr[i];
        for(int j = i; j<n; j++){
            if(arr[j] == arr[i]) break;
        }
    }

    printf("The duplicate element in the array is : %d", temp);

    return 0;
}