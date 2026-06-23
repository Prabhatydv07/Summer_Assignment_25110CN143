#include<stdio.h>
#include<string.h>

int main(){
    char str[50];
    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin); //taking string as an input
    str[strcspn(str, "\n")] = '\0'; 

    int n = strlen(str);

    char firstch = '\0';

    for(int i = 0; i<n; i++){
        int isrepeating = 0;
        for(int j = 0; j<n;j++){
            if(i!=j && str[i] == str[j]){ //check entire string skip itself
                isrepeating = 1;
                break;
            }
        }
        if(!isrepeating){
            firstch = str[i];
            break;//stop at first non repeating character 
        }
    }

    printf("The first non repeating character in the string is : %c", firstch);
    return 0;
}