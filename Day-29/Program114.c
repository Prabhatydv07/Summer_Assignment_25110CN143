/*
 * ============================================================
 *  MENU-DRIVEN ARRAY OPERATIONS SYSTEM IN C
 * ============================================================
 *
 *  Operations covered:
 *   1. Input elements
 *   2. Display elements
 *   3. Insert an element at a given position
 *   4. Delete an element by value
 *   5. Search for an element (Linear Search)
 *   6. Sort the array (Bubble Sort)
 *   7. Reverse the array
 *   8. Find minimum & maximum
 *   9. Calculate sum & average
 *  10. Exit
 * ============================================================
 */

#include <stdio.h>   /* printf, scanf */
#include <stdlib.h>  /* exit()        */

/* ── Constants ─────────────────────────────────────────────── */
#define MAX_SIZE 100   /* Maximum number of elements the array can hold */

/* ── Function Prototypes ────────────────────────────────────── */
void inputArray   (int arr[], int *n);
void displayArray (const int arr[], int n);
void insertElement(int arr[], int *n, int pos, int value);
void deleteElement(int arr[], int *n, int value);
int  searchElement(const int arr[], int n, int value);
void bubbleSort   (int arr[], int n);
void reverseArray (int arr[], int n);
void findMinMax   (const int arr[], int n);
void sumAverage   (const int arr[], int n);
void printMenu    (void);


/* ================================================================
 *  MAIN – Entry point
 * ================================================================ */
int main(void)
{
    int arr[MAX_SIZE]; /* The array that holds our data           */
    int n = 0;         /* Current number of elements in the array */
    int choice;        /* Stores the user's menu selection        */
    int pos, value;    /* Temporary variables for insert/delete   */

    printf("========================================\n");
    printf("   MENU-DRIVEN ARRAY OPERATIONS SYSTEM  \n");
    printf("========================================\n");

    /* ── Main program loop ──────────────────────────────────── */
    do {
        printMenu();                          /* Show options      */
        printf("Enter your choice: ");
        scanf("%d", &choice);                 /* Read user input   */

        switch (choice)
        {
            /* ── 1. Input ─────────────────────────────────── */
            case 1:
                inputArray(arr, &n);
                break;

            /* ── 2. Display ───────────────────────────────── */
            case 2:
                displayArray(arr, n);
                break;

            /* ── 3. Insert ────────────────────────────────── */
            case 3:
                if (n >= MAX_SIZE) {
                    printf("[!] Array is full. Cannot insert.\n");
                    break;
                }
                printf("Enter position (0-based index, 0 to %d): ", n);
                scanf("%d", &pos);
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertElement(arr, &n, pos, value);
                break;

            /* ── 4. Delete ────────────────────────────────── */
            case 4:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteElement(arr, &n, value);
                break;

            /* ── 5. Search ────────────────────────────────── */
            case 5:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                printf("Enter value to search: ");
                scanf("%d", &value);
                pos = searchElement(arr, n, value);
                if (pos != -1)
                    printf("[✓] Found %d at index %d.\n", value, pos);
                else
                    printf("[✗] %d not found in array.\n", value);
                break;

            /* ── 6. Sort ──────────────────────────────────── */
            case 6:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                bubbleSort(arr, n);
                printf("[✓] Array sorted in ascending order.\n");
                displayArray(arr, n);
                break;

            /* ── 7. Reverse ───────────────────────────────── */
            case 7:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                reverseArray(arr, n);
                printf("[✓] Array reversed.\n");
                displayArray(arr, n);
                break;

            /* ── 8. Min & Max ─────────────────────────────── */
            case 8:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                findMinMax(arr, n);
                break;

            /* ── 9. Sum & Average ─────────────────────────── */
            case 9:
                if (n == 0) {
                    printf("[!] Array is empty.\n");
                    break;
                }
                sumAverage(arr, n);
                break;

            /* ── 10. Exit ─────────────────────────────────── */
            case 10:
                printf("Goodbye!\n");
                break;

            /* ── Invalid input ────────────────────────────── */
            default:
                printf("[!] Invalid choice. Please enter 1-10.\n");
        }

        printf("\n");

    } while (choice != 10);   /* Loop until the user chooses Exit */

    return 0;
}


/* ================================================================
 *  FUNCTION DEFINITIONS
 * ================================================================ */

/* ── printMenu ───────────────────────────────────────────────── */
/* Displays the list of operations to the user.                   */
void printMenu(void)
{
    printf("----------------------------------------\n");
    printf(" 1. Input elements\n");
    printf(" 2. Display elements\n");
    printf(" 3. Insert element at position\n");
    printf(" 4. Delete element by value\n");
    printf(" 5. Search element (Linear Search)\n");
    printf(" 6. Sort array (Bubble Sort)\n");
    printf(" 7. Reverse array\n");
    printf(" 8. Find Min & Max\n");
    printf(" 9. Sum & Average\n");
    printf("10. Exit\n");
    printf("----------------------------------------\n");
}


/* ── inputArray ──────────────────────────────────────────────── */
/* Reads 'n' integer values from the user and stores them.        */
void inputArray(int arr[], int *n)
{
    printf("How many elements (max %d)? ", MAX_SIZE);
    scanf("%d", n);

    /* Validate size */
    if (*n <= 0 || *n > MAX_SIZE) {
        printf("[!] Invalid size. Choose between 1 and %d.\n", MAX_SIZE);
        *n = 0;
        return;
    }

    printf("Enter %d element(s):\n", *n);
    for (int i = 0; i < *n; i++) {
        printf("  arr[%d] = ", i);
        scanf("%d", &arr[i]);     /* Store each element at index i */
    }
    printf("[✓] Array loaded with %d element(s).\n", *n);
}


/* ── displayArray ────────────────────────────────────────────── */
/* Prints all elements currently stored in the array.             */
void displayArray(const int arr[], int n)
{
    if (n == 0) {
        printf("[!] Array is empty.\n");
        return;
    }

    printf("Array (%d element(s)): [ ", n);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");   /* Comma between elements */
    }
    printf(" ]\n");
}


/* ── insertElement ───────────────────────────────────────────── */
/* Inserts 'value' at the given 0-based 'pos', shifting elements  */
/* to the right.                                                  */
void insertElement(int arr[], int *n, int pos, int value)
{
    /* Validate position */
    if (pos < 0 || pos > *n) {
        printf("[!] Invalid position. Must be between 0 and %d.\n", *n);
        return;
    }

    /*
     * Shift every element from the last position down to 'pos'
     * one step to the right to make room for the new value.
     *
     *  Before: [10, 20, 30, 40]   insert 99 at pos 2
     *  Shift:  [10, 20, 30, 30, 40]  (copy 30->index3, 40->index4)
     *  After:  [10, 20, 99, 30, 40]
     */
    for (int i = *n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = value;   /* Place the new value at the target position */
    (*n)++;             /* Increment element count                    */

    printf("[✓] Inserted %d at index %d.\n", value, pos);
    displayArray(arr, *n);
}


/* ── deleteElement ───────────────────────────────────────────── */
/* Searches for the first occurrence of 'value' and removes it    */
/* by shifting elements left.                                     */
void deleteElement(int arr[], int *n, int value)
{
    /* First locate the element */
    int pos = searchElement(arr, *n, value);

    if (pos == -1) {
        printf("[✗] %d not found. Nothing deleted.\n", value);
        return;
    }

    /*
     * Overwrite the element at 'pos' by shifting everything
     * after it one step to the left.
     *
     *  Before: [10, 20, 99, 30, 40]  delete 99 (index 2)
     *  After:  [10, 20, 30, 40]
     */
    for (int i = pos; i < *n - 1; i++) {
        arr[i] = arr[i + 1];
    }

    (*n)--;   /* Reduce the element count by one */

    printf("[✓] Deleted first occurrence of %d (was at index %d).\n",
           value, pos);
    displayArray(arr, *n);
}


/* ── searchElement ───────────────────────────────────────────── */
/* Linear Search: checks each element one by one.                 */
/* Returns the index of the first match, or -1 if not found.      */
int searchElement(const int arr[], int n, int value)
{
    for (int i = 0; i < n; i++) {
        if (arr[i] == value)   /* Match found */
            return i;
    }
    return -1;   /* Value not present */
}


/* ── bubbleSort ──────────────────────────────────────────────── */
/* Sorts the array in ascending order using the Bubble Sort algo. */
/*                                                                */
/* How Bubble Sort works:                                         */
/*   Repeatedly compare adjacent pairs and swap them if they are  */
/*   in the wrong order.  After each full pass, the largest        */
/*   unsorted element "bubbles up" to its correct position.       */
void bubbleSort(int arr[], int n)
{
    int temp;
    int swapped;   /* Flag to detect if any swap happened in a pass */

    for (int i = 0; i < n - 1; i++) {          /* Outer pass         */
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++) {  /* Inner comparison   */
            if (arr[j] > arr[j + 1]) {
                /* Swap adjacent elements */
                temp       = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = temp;
                swapped    = 1;
            }
        }

        /* If no swaps occurred the array is already sorted; stop early */
        if (!swapped)
            break;
    }
}


/* ── reverseArray ────────────────────────────────────────────── */
/* Reverses the array in-place by swapping elements from both     */
/* ends towards the centre.                                       */
void reverseArray(int arr[], int n)
{
    int left  = 0;       /* Pointer starting at the beginning */
    int right = n - 1;   /* Pointer starting at the end       */
    int temp;

    while (left < right) {
        /* Swap arr[left] and arr[right] */
        temp        = arr[left];
        arr[left]   = arr[right];
        arr[right]  = temp;

        left++;    /* Move left pointer inward  */
        right--;   /* Move right pointer inward */
    }
}


/* ── findMinMax ──────────────────────────────────────────────── */
/* Scans the array once to find the smallest and largest values.  */
void findMinMax(const int arr[], int n)
{
    int min = arr[0];   /* Assume first element is both min and max */
    int max = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];   /* Update min if smaller found */
        if (arr[i] > max) max = arr[i];   /* Update max if larger  found */
    }

    printf("Minimum value : %d\n", min);
    printf("Maximum value : %d\n", max);
}


/* ── sumAverage ──────────────────────────────────────────────── */
/* Calculates the total sum and arithmetic mean of all elements.  */
void sumAverage(const int arr[], int n)
{
    long long sum = 0;   /* Use long long to avoid overflow for large arrays */

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double avg = (double)sum / n;   /* Cast to double for decimal result */

    printf("Sum     : %lld\n", sum);
    printf("Average : %.2f\n", avg);  /* Two decimal places */
}