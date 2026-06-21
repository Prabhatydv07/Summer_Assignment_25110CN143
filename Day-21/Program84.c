#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    char upstr[50];
    int i = 0;
    for(i = 0; str[i] != '\0' ; i++){
        if(str[i] == 'a') upstr[i] = 'A';
        else if (str[i] == 'b') upstr[i] = 'B';
        else if (str[i] == 'c') upstr[i] = 'C';
        else if (str[i] == 'd') upstr[i] = 'D';
        else if (str[i] == 'e') upstr[i] = 'E';
        else if (str[i] == 'f') upstr[i] = 'F';
        else if (str[i] == 'g') upstr[i] = 'G';
        else if (str[i] == 'h') upstr[i] = 'H';
        else if (str[i] == 'i') upstr[i] = 'I';
        else if (str[i] == 'j') upstr[i] = 'J';
        else if (str[i] == 'k') upstr[i] = 'K';
        else if (str[i] == 'l') upstr[i] = 'L';
        else if (str[i] == 'm') upstr[i] = 'M';
        else if (str[i] == 'n') upstr[i] = 'N';
        else if (str[i] == 'o') upstr[i] = 'O';
        else if (str[i] == 'p') upstr[i] = 'P';
        else if (str[i] == 'q') upstr[i] = 'Q';
        else if (str[i] == 'r') upstr[i] = 'R';
        else if (str[i] == 's') upstr[i] = 'S';
        else if (str[i] == 't') upstr[i] = 'T';
        else if (str[i] == 'u') upstr[i] = 'U';
        else if (str[i] == 'v') upstr[i] = 'V';
        else if (str[i] == 'w') upstr[i] = 'W';
        else if (str[i] == 'x') upstr[i] = 'X';
        else if (str[i] == 'y') upstr[i] = 'Y';
        else if (str[i] == 'z') upstr[i] = 'Z';
    }
    upstr[i] = '\0'; //adding null character at the end to make it a string

    printf("The uppercase string is : ");
        for(int i = 0; upstr[i] != '\0'; i++){
            printf("%c ", upstr[i]);
        }
    
}