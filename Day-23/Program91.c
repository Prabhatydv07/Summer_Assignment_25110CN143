#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    char str1[100], str2[100];

    printf("Enter first string  : ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string : ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';

    // if lengths differ, cannot be anagram
    if(strlen(str1) != strlen(str2)){
        printf("Strings are NOT anagrams.\n");
        return 0;
    }

    int freq[26] = {0};  // frequency array for a-z

    int n = strlen(str1);

    for(int i = 0; i < n; i++){
        freq[tolower(str1[i]) - 'a']++;  // increment for str1
        freq[tolower(str2[i]) - 'a']--;  // decrement for str2
    }

    // if all frequencies are 0, strings are anagrams
    int isAnagram = 1;
    for(int i = 0; i < 26; i++){
        if(freq[i] != 0){
            isAnagram = 0;
            break;
        }
    }

    if(isAnagram)
        printf("Strings ARE anagrams.\n");
    else
        printf("Strings are NOT anagrams.\n");

    return 0;
}