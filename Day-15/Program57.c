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

    int i = 0, j=n-1;

    while(i<j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    printf("The reversed array is - \n");
    for(int i = 0; i<n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}