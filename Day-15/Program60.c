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

    int count = 0;
    for(int i = 0; i<n; i++){
        if(arr[i] == 0){
            count++;
        }
    }

    int k = n-1;
    while(count != 0){
        arr[k] = 0;
        count--;
        k--;
    }

    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}