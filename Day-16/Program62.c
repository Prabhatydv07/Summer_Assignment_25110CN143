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

    int maxfeq = 0, maxele = arr[0];
    
    for(int i = 0; i<n; i++){
        int freq = 0;
        for(int j = i; j<n; j++){
            if(arr[j] == arr[i]){
                freq++;
            }
        }
        if(freq > maxfeq){
            maxfeq = freq;
            maxele = arr[i];
        }
    }

    printf("The maximum frequency element in the array is : %d", maxele);
    return 0;
}