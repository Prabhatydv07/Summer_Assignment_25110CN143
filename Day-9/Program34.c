#include<stdio.h>

int main(){
    int n;
    printf("Enter the number of rows :");
    scanf("%d", &n);

    for(int i = 0; i<n; i++){
        int count = 1;
        for(int j = n; j>i ; j--){
            printf("%d ", count);
            count++;
        }
        printf("\n");
    }
}