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

    int rot;
    printf("Enter the number of rotations of array : ");
    scanf("%d", &rot);

    int i = 0, j = rot-1;

    while(i<j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }

    int k = rot, l= n-1;
    while(k<l){
        int temp = arr[k] ;
        arr[k] = arr[l];
        arr[l] = temp;
        k++;
        l--;
    }

    int m = 0, o = n -1;
    while(m<o){
        int temp = arr[m];
        arr[m] = arr[o];
        arr[o] = temp;
        m++;
        o--;
    }

    printf("The rotated array is : ");
    for(int i = 0 ; i<n; i++){
        printf("%d ", arr[i]);
    }

    return 0;
}