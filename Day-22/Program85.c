#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    char strrev[50];

    int n = strlen(str);

    for( int i = 0; i<n; i++){  
        strrev[i] = str[n - 1-i];//storing the reversed string 
    }
    strrev[n] = '\0';

    int isrev = 1;
    for( int j = 0; str[j] != '\0'; j++){
        if(str[j] != strrev[j]) isrev = 0;
    }

    if (isrev)
    {
        printf("The eneterd string is palindrome");
    }

    else{
        printf("The eneterd string is not palindrome");
    }
    

    return 0;
}