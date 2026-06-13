#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];

    for(int i = 0; i<n; i++){
        printf("Entert %d element : ", i );
        scanf("%d", &arr[i]);
    }

    printf("The array is : ");

    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}