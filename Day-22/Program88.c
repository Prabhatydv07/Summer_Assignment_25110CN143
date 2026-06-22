#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 
    
    char str1[50]; //new string calculated since string is immutable

    int n = strlen(str);

    int i ;
    for( i = 0; i<n; i++){  
        if(str[i] == ' ') continue;
        else{
            str1[i] = str[i];
        }
    }
    str1[i] = '\0';

    printf("The string after removing spaces from it is : ");
    for(int j = 0; str1[j] != '\0'; j++){
        printf("%c", str1[j]);
    }


    return 0;
}