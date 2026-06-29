/*
 * ============================================================
 *  MENU-DRIVEN STRING OPERATIONS SYSTEM IN C
 * ============================================================
 *
 *  All string functions are implemented MANUALLY (no string.h)
 *  so you can see exactly how each algorithm works.
 *
 *  Operations:
 *   1.  Input a string
 *   2.  Display the string
 *   3.  Find string length
 *   4.  Reverse the string
 *   5.  Check if Palindrome
 *   6.  Convert to Uppercase
 *   7.  Convert to Lowercase
 *   8.  Count Vowels, Consonants, Digits & Spaces
 *   9.  Copy string to another string
 *  10.  Concatenate two strings
 *  11.  Compare two strings
 *  12.  Search for a substring
 *  13.  Replace a character
 *  14.  Count word frequency
 *  15.  Exit
 * ============================================================
 */

#include <stdio.h>    /* printf, scanf, getchar */
#include <stdlib.h>   /* exit()                 */

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_LEN  500   /* Maximum length of any string */

/* ── Helper: flush leftover characters from input buffer ─────── */
/*   Without this, leftover '\n' breaks the next scanf / fgets.   */
void flushInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ── Helper: read a full line (including spaces) safely ─────── */
void readLine(char str[], int maxLen)
{
    int i = 0;
    int c;
    /* Read characters one by one until newline or buffer limit  */
    while (i < maxLen - 1 && (c = getchar()) != '\n' && c != EOF) {
        str[i++] = (char)c;
    }
    str[i] = '\0';   /* Null-terminate the string */
}

/* ================================================================
 *  OWN IMPLEMENTATIONS  (no <string.h> functions used)
 * ================================================================ */

/* ── myStrLen ────────────────────────────────────────────────── */
/* Counts characters until the null terminator '\0'.              */
int myStrLen(const char str[])
{
    int len = 0;
    while (str[len] != '\0')   /* Walk until end of string */
        len++;
    return len;
}

/* ── myStrCopy ───────────────────────────────────────────────── */
/* Copies every character from src to dest, including '\0'.       */
void myStrCopy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];   /* Copy character by character */
        i++;
    }
    dest[i] = '\0';         /* Don't forget the null terminator */
}

/* ── myStrConcat ─────────────────────────────────────────────── */
/* Appends src to the end of dest.                                */
/* Finds the end of dest first, then copies src from there.       */
void myStrConcat(char dest[], const char src[])
{
    int i = myStrLen(dest);   /* Start writing after dest's last char */
    int j = 0;
    while (src[j] != '\0') {
        dest[i++] = src[j++];
    }
    dest[i] = '\0';           /* Null-terminate the combined result */
}

/* ── myStrCompare ────────────────────────────────────────────── */
/* Compares two strings character by character.                   */
/* Returns: 0 if equal, >0 if str1 > str2, <0 if str1 < str2     */
int myStrCompare(const char str1[], const char str2[])
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i])
            return str1[i] - str2[i];   /* Difference in ASCII values */
        i++;
    }
    /* If one string ended before the other */
    return str1[i] - str2[i];
}

/* ── myStrStr ────────────────────────────────────────────────── */
/* Searches for 'pattern' inside 'text'.                          */
/* Returns the index of the first match, or -1 if not found.      */
int myStrStr(const char text[], const char pattern[])
{
    int tLen = myStrLen(text);
    int pLen = myStrLen(pattern);

    for (int i = 0; i <= tLen - pLen; i++) {
        int j;
        /* Try to match pattern starting at position i in text */
        for (j = 0; j < pLen; j++) {
            if (text[i + j] != pattern[j])
                break;   /* Mismatch — try next position */
        }
        if (j == pLen)
            return i;    /* Full pattern matched at index i */
    }
    return -1;   /* Pattern not found */
}

/* ── reverseString ───────────────────────────────────────────── */
/* Reverses str in-place using two-pointer swap technique.         */
void reverseString(char str[])
{
    int left  = 0;
    int right = myStrLen(str) - 1;
    char temp;

    while (left < right) {
        temp       = str[left];
        str[left]  = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

/* ── toUpperCase ─────────────────────────────────────────────── */
/* Converts every lowercase letter (a-z) to uppercase (A-Z).     */
/* ASCII trick: 'a' = 97, 'A' = 65, difference = 32.             */
void toUpperCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] = str[i] - 32;   /* Subtract 32 to get uppercase */
    }
}

/* ── toLowerCase ─────────────────────────────────────────────── */
/* Converts every uppercase letter (A-Z) to lowercase (a-z).     */
void toLowerCase(char str[])
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;   /* Add 32 to get lowercase */
    }
}

/* ── isPalindrome ────────────────────────────────────────────── */
/* A palindrome reads the same forwards and backwards.            */
/* Strategy: compare a reversed copy with the original.           */
int isPalindrome(const char str[])
{
    char copy[MAX_LEN];
    myStrCopy(copy, str);
    reverseString(copy);
    return myStrCompare(str, copy) == 0;   /* 1 = yes, 0 = no */
}

/* ── countCharTypes ──────────────────────────────────────────── */
/* Counts vowels, consonants, digits, and spaces in a string.     */
void countCharTypes(const char str[])
{
    int vowels = 0, consonants = 0, digits = 0, spaces = 0, other = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == ' ' || c == '\t') {
            spaces++;
        }
        else if (c >= '0' && c <= '9') {
            digits++;
        }
        else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            /* Check if the letter is a vowel */
            char lower = (c >= 'A' && c <= 'Z') ? c + 32 : c;
            if (lower=='a' || lower=='e' || lower=='i' || lower=='o' || lower=='u')
                vowels++;
            else
                consonants++;
        }
        else {
            other++;   /* Punctuation, symbols, etc. */
        }
    }

    printf("  Vowels     : %d\n", vowels);
    printf("  Consonants : %d\n", consonants);
    printf("  Digits     : %d\n", digits);
    printf("  Spaces     : %d\n", spaces);
    printf("  Others     : %d\n", other);
}

/* ── replaceChar ─────────────────────────────────────────────── */
/* Replaces every occurrence of 'oldCh' with 'newCh'.             */
int replaceChar(char str[], char oldCh, char newCh)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == oldCh) {
            str[i] = newCh;
            count++;
        }
    }
    return count;   /* Returns how many replacements were made */
}

/* ── countWords ──────────────────────────────────────────────── */
/* Counts words by detecting transitions from space to non-space. */
int countWords(const char str[])
{
    int count = 0;
    int inWord = 0;   /* Flag: are we currently inside a word? */

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            if (!inWord) {
                count++;     /* New word started */
                inWord = 1;
            }
        } else {
            inWord = 0;      /* Space encountered — left the word */
        }
    }
    return count;
}

/* ── printMenu ───────────────────────────────────────────────── */
void printMenu(void)
{
    printf("\n==========================================\n");
    printf("     STRING OPERATIONS MENU\n");
    printf("==========================================\n");
    printf("  1.  Input a string\n");
    printf("  2.  Display the string\n");
    printf("  3.  Find string length\n");
    printf("  4.  Reverse the string\n");
    printf("  5.  Check if Palindrome\n");
    printf("  6.  Convert to Uppercase\n");
    printf("  7.  Convert to Lowercase\n");
    printf("  8.  Count Vowels / Consonants / Digits / Spaces\n");
    printf("  9.  Copy string to another variable\n");
    printf(" 10.  Concatenate two strings\n");
    printf(" 11.  Compare two strings\n");
    printf(" 12.  Search for a substring\n");
    printf(" 13.  Replace a character\n");
    printf(" 14.  Count number of words\n");
    printf(" 15.  Exit\n");
    printf("==========================================\n");
}


/* ================================================================
 *  MAIN
 * ================================================================ */
int main(void)
{
    char str[MAX_LEN]  = "";   /* Primary string — starts empty   */
    char str2[MAX_LEN] = "";   /* Secondary string for operations  */
    int  choice;

    printf("\n******************************************\n");
    printf("*   MENU-DRIVEN STRING OPERATIONS IN C  *\n");
    printf("******************************************\n");

    do {
        printMenu();
        printf("Enter your choice (1-15): ");

        /*
         * Guard scanf: if user types a non-integer,
         * clear the buffer and ask again.
         */
        if (scanf("%d", &choice) != 1) {
            flushInput();
            printf("[!] Please enter a number between 1 and 15.\n");
            choice = 0;
            continue;
        }
        flushInput();   /* Remove leftover '\n' after the number */

        switch (choice)
        {
            /* ── 1. Input ─────────────────────────────────────── */
            case 1:
                printf("Enter a string: ");
                readLine(str, MAX_LEN);
                printf("[+] String stored.\n");
                break;

            /* ── 2. Display ────────────────────────────────────── */
            case 2:
                if (str[0] == '\0') {
                    printf("[!] No string entered yet.\n");
                } else {
                    printf("String : \"%s\"\n", str);
                }
                break;

            /* ── 3. Length ─────────────────────────────────────── */
            case 3:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("Length of \"%s\" = %d\n", str, myStrLen(str));
                break;

            /* ── 4. Reverse ────────────────────────────────────── */
            case 4:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                reverseString(str);
                printf("[+] Reversed string : \"%s\"\n", str);
                break;

            /* ── 5. Palindrome ─────────────────────────────────── */
            case 5:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                if (isPalindrome(str))
                    printf("[+] \"%s\" IS a palindrome.\n", str);
                else
                    printf("[-] \"%s\" is NOT a palindrome.\n", str);
                break;

            /* ── 6. Uppercase ──────────────────────────────────── */
            case 6:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                toUpperCase(str);
                printf("[+] Uppercase : \"%s\"\n", str);
                break;

            /* ── 7. Lowercase ──────────────────────────────────── */
            case 7:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                toLowerCase(str);
                printf("[+] Lowercase : \"%s\"\n", str);
                break;

            /* ── 8. Count char types ───────────────────────────── */
            case 8:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("Character breakdown of \"%s\":\n", str);
                countCharTypes(str);
                break;

            /* ── 9. Copy ───────────────────────────────────────── */
            case 9:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                myStrCopy(str2, str);
                printf("[+] Copied to str2 : \"%s\"\n", str2);
                break;

            /* ── 10. Concatenate ───────────────────────────────── */
            case 10:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("Enter string to append: ");
                readLine(str2, MAX_LEN);
                /* Safety check: ensure concat won't overflow buffer */
                if (myStrLen(str) + myStrLen(str2) >= MAX_LEN) {
                    printf("[!] Result would exceed buffer. Aborting.\n");
                    break;
                }
                myStrConcat(str, str2);
                printf("[+] After concatenation : \"%s\"\n", str);
                break;

            /* ── 11. Compare ───────────────────────────────────── */
            case 11:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("Enter second string to compare: ");
                readLine(str2, MAX_LEN);
                {
                    int result = myStrCompare(str, str2);
                    if (result == 0)
                        printf("[=] Strings are EQUAL.\n");
                    else if (result > 0)
                        printf("[>] \"%s\" is GREATER than \"%s\".\n", str, str2);
                    else
                        printf("[<] \"%s\" is LESS than \"%s\".\n", str, str2);
                }
                break;

            /* ── 12. Substring search ──────────────────────────── */
            case 12:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("Enter substring to search: ");
                readLine(str2, MAX_LEN);
                {
                    int idx = myStrStr(str, str2);
                    if (idx != -1)
                        printf("[+] \"%s\" found at index %d.\n", str2, idx);
                    else
                        printf("[-] \"%s\" not found in \"%s\".\n", str2, str);
                }
                break;

            /* ── 13. Replace character ─────────────────────────── */
            case 13:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                {
                    char oldCh, newCh;
                    printf("Enter character to replace: ");
                    oldCh = (char)getchar(); flushInput();
                    printf("Enter replacement character: ");
                    newCh = (char)getchar(); flushInput();
                    int n = replaceChar(str, oldCh, newCh);
                    printf("[+] Replaced %d occurrence(s). Result: \"%s\"\n", n, str);
                }
                break;

            /* ── 14. Word count ────────────────────────────────── */
            case 14:
                if (str[0] == '\0') { printf("[!] No string entered.\n"); break; }
                printf("[+] Word count in \"%s\" = %d\n", str, countWords(str));
                break;

            /* ── 15. Exit ──────────────────────────────────────── */
            case 15:
                printf("\nGoodbye!\n");
                break;

            default:
                printf("[!] Invalid choice. Enter 1 to 15.\n");
        }

    } while (choice != 15);

    return 0;
}