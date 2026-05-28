#include<stdio.h>

int main(){
    int n, count =0; 
    printf("Enter the number to count digits :" );
    scanf("%d", &n);

    while(n!= 0){
        count += 1;
        n /= 10;
    }

    printf("The number of digits  is %d", count );
    return 0;
}