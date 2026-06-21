#include<stdio.h>
#include<string.h>

char* revstr(char str[]){
    static char str2[100];  //new str created since string is immutable
    int len = strlen(str);
    int end = len - 1;
    int st = 0; 
    while(st < len){ //swaping last element with the first one
        str2[st] = str[end];
        st++;
        end--;
    }
    str2[st] = '\0';
    return str2;
}

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    char strrev[50];
    strcpy(strrev, revstr(str));

    printf("The reversed string is : "); 
    for(int i = 0; strrev[i] != '\0'; i++){  //Printing the reversed string
        printf("%c ", strrev[i]);
    }

    return 0;
}