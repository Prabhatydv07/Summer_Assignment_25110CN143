#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    int vcount = 0, ccount = 0;
    for(int i = 0; str[i]!= '\0'; i++){
        if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' 
        || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U'){
            vcount++; //conunting number of vowels 
        }
        else ccount++; //counting number of consonents
    }

    printf("The number of vovels are : %d", vcount);
    printf("The number of consonenets are : %d", ccount);
}