#include<stdio.h>

int main(){
    int a, b;
    
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    
    int x = a, y = b;  // save originals for display
    
    while(b != 0){
        int temp = b;
        b = a % b;
        a = temp;
    }
    
    printf("GCD of %d and %d is: %d\n", x, y, a);
    return 0;
}