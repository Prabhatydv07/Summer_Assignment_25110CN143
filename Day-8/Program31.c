#include<stdio.h>

int main(){
    int n;
    printf("Enter the no of rows : ");
    scanf("%d", &n);

    for(int i = 0; i<n; i++){ // for no of rows
        for(int j = 65; j<65 + i; j++){
            printf("%c ", (char)j); //char type conversion 
        }
        printf("\n");
    }
    return 0;
}