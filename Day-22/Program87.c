#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 
    
    int charcount = 0;

    int wcount = 1;
    for(int i =0; str[i] != '\0'; i++){
        charcount++;
    }

    printf("The number of characters in the enterd string is : %d", charcount);
    return 0;
}