#include <stdio.h>
#include<math.h>

int isArmstrong(int n) {
    int original = n, sum = 0, digits = 0, temp = n;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = n;
    while (temp != 0) {
        int d = temp % 10;
        sum += pow(d, digits);
        temp /= 10;
    }

    return sum == original;
}


int main(){
    int start, stop = 0;
    printf("Enter the starting point : ");
    scanf("%d", &start);

    printf("Enter the ending point : ");
    scanf("%d", &stop);

    printf("Armstrong number in given range are : ");

    for(int i = start; i<=stop; i++){
        if(isArmstrong(i)){
            printf("%d ", i);
        }
    }
    return 0;
}