#include<stdio.h>

int main(){
    int n; 
    printf("Enter the length of the array : ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the elements of the array");
    for(int i = 0; i<n;i++){
        scanf("%d", &arr[i]);
    }

    //Selection sort
        for(int i = 0; i<n-1; i++){
            int min = 10000;
            int mindx = -1;
            for(int j = i; j<n;j++){
                if(arr[j]<min){
                    min = arr[j];
                    mindx = j;
                }
            }

            //swap
            int temp = arr[i];
            arr[i] = arr[mindx];
            arr[mindx] = temp;
        }

    printf("The sorted array is : \n");
    for(int i = 0; i<n;i++){
        printf("%d \\\\", arr[i]);
    }

    return 0;
}