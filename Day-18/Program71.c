#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array : ");
    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int search;
    printf("Enter the element to search : ");
    scanf("%d", &search);

    int flag = 0,indx = 0;
    for(int i = 0; i<n;i++){
        if(arr[i] == search){
            flag = 1;
            indx = i;
        }
    }

    if(flag == 1){
        printf("The element fond in array at %d postion !!",indx);
    }

    else{
        printf("The element is not presnt in the array");
    }
    return 0;
}