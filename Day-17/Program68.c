#include<stdio.h>

int main(){
    int n;
    printf("Enter the length of array 1 : ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the array elements : ");
    for(int i = 0 ; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int m;
    printf("Enter the length of array 2 : ");
    scanf("%d", &m);
    int arr1[m];

    printf("Enter the elements of second array : ");
    for(int i = 0; i<m; i++){
        scanf("%d", &arr1[i]);
    }

    int minLen = (m < n) ? m : n; 
    int arr2[minLen];
    int k = 0;  // count of common elements

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i] == arr1[j]) {   // ✅ check every pair
                arr2[k++] = arr[i];
                break;  // 
            }
        }
    }

    printf("The elemnts common in both the array are : ");

    for(int i = 0 ; i<k; i++){
        printf("%d  ", arr2[i]);
    }


    return 0;

}