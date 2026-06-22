#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    int wcount = 1;
    for(int i =0; str[i] != '\0'; i++){
        if(str[i] == ' ') wcount++;
    }

    printf("The number of words in the eneterd string are : %d", wcount);
    return 0;
}