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

    int target = 0;
    printf("Enter the sum : ");
    scanf("%d", &target);

    int first = 0, second = 0 , flag = 0;
    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            if(arr[i] + arr[j] == target){
                first = arr[i];
                second = arr[j];
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }

    if(flag){
        printf("The pair of element with sum %d are %d and %d", target,first,second);
    }
    else{
        printf("NO pair found with the target sum \n");
    }
    return 0;
}