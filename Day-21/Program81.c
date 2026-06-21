#include<stdio.h>

int lenstr(char str[]){
    int len = -1; //-1 used to cancel \n 
    for(int i = 0; str[i] != '\0' ; i++){
        len++;
    }
    return len ;
}

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str,sizeof(str), stdin);

    int len = lenstr(str); //len funcion called

    printf("The length of the sting is : %d", len);

    return 0;
}