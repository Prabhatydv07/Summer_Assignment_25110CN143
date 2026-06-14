#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];

    int find, ind , flag= 0;
    printf("Enter the element to be searched :");
    scanf("%d", &find);

    for(int i = 0; i<n; i++){
        if(arr[i] == find){
            flag = 1;
            ind = i;
        }
    }

    if(flag){
        printf("The element exist in the array at %d index ", ind);
    }

    else{
        printf("The element is not found in the array ");
    }
    return 0;
}