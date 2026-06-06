#include<stdio.h>

double fact(int n){  //double type for large numbers factorial 
    if(n == 1 || n == 0){
        return 1;
    }

    else{
        return(fact(n-1) * (n));
    }
}

int main(){
    int n;
    printf("Enter the number : ");
    scanf("%d", &n);

    double result = fact(n); //result store in double type

    printf("Facorial of %d is : %.0lf", n , result);
    return 0;
}