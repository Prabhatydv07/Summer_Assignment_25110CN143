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

    for(int i = 0; i<n; i++){
        for(int j = i; j<n; j++){
            if(arr[j] == arr[i]){
                arr[i] = arr[i+1];
            }
        }
    }
    return 0;
}