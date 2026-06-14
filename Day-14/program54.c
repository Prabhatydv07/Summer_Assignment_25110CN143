#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of elements in the array : ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the array : \n");

    for(int i = 0; i<n;i++){
        scanf("%d", &arr[i]);
    }

    int search, count = 0;
    printf("Enter the ement to count frequency : ");
    scanf("%d", &search);

    for(int i = 0 ;i<n; i++){
        if(arr[i] == search) count++;
    }

    printf("The frequency of %d is : %d", search,count);
    return 0;
}