#include<stdio.h>

int main(){
    int start , end , isprime = 0;
    printf("Enter the starting point : ");
    scanf("%d", &start);

    printf("Enter the ending number : ");
    scanf("%d", &end);

    printf("Prime numbers between %d and %d are : ");

    for(int i = start; i<=end ;i ++){
        if(i<2) continue;

        isprime = 1;

        for(int j = 2; j*j<=i;j++){
            if(i%j == 0){
                isprime = 0 ;
                break;
            }
        }

        if(isprime)
            printf("%d ", i);
    }


    return 0;
}