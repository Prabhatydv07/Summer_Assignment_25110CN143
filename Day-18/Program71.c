#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array:");
    for(int i = 0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int target ;
    printf("Enter the element to find : ");
    scanf("%d", &target);
    int indx = 0, found = 0;

    int lo = 0, hi = n-1;
    while(lo<=hi){
        int mid = (lo + hi) /2;
        if(arr[mid]<target) lo = mid + 1;
        else if(arr[mid]>target) hi = mid -1;
        else{
            indx = mid;
            found = 1;
            break;
        }
    }

    if(found){
        printf("The element found at array at %d index", indx);
    }

    else{
        printf("The element is not present in the array");
    }

    return 0;
}