#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char str[100];

    printf("Enter the string : ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    int n = strlen(str);
    int freq[26] = {0};  // frequency array for a-z

    // count frequency of each character
    for(int i = 0; i < n; i++){
        if(isalpha(str[i])){                    // ignore spaces, digits, symbols
            freq[tolower(str[i]) - 'a']++;      // case-insensitive counting
        }
    }

    // find the maximum frequency
    int maxFreq = 0;
    for(int i = 0; i < 26; i++){
        if(freq[i] > maxFreq){
            maxFreq = freq[i];
        }
    }

    // print all characters with maximum frequency
    printf("Maximum occurring character(s) with frequency %d : ", maxFreq);
    for(int i = 0; i < 26; i++){
        if(freq[i] == maxFreq){
            printf("'%c' ", 'a' + i);           // convert index back to character
        }
    }
    printf("\n");

    return 0;
}