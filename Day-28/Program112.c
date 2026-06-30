/*
 * Contact Management System
 * --------------------------
 * A simple console-based contact manager written in C.
 * Features:
 *   - Add contact
 *   - View all contacts
 *   - Search contact (by name or phone)
 *   - Update contact
 *   - Delete contact
 *   - Save to / Load from file (contacts.dat) for persistence
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTACTS 1000
#define NAME_LEN     50
#define PHONE_LEN    15
#define EMAIL_LEN    50
#define FILE_NAME    "contacts.dat"

typedef struct {
    int  id;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

Contact contacts[MAX_CONTACTS];
int contactCount = 0;
int nextId = 1;

/* ---------- Utility Functions ---------- */

/* Clears leftover characters in stdin after scanf */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Reads a line of text safely into buffer */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

/* Converts a string to lowercase (for case-insensitive search) */
void toLowerStr(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = (char) tolower((unsigned char) src[i]);
        i++;
    }
    dest[i] = '\0';
}

/* ---------- File Handling ---------- */

void saveContacts(void) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Error: Could not save contacts to file.\n");
        return;
    }
    fwrite(&nextId, sizeof(int), 1, fp);
    fwrite(&contactCount, sizeof(int), 1, fp);
    fwrite(contacts, sizeof(Contact), contactCount, fp);
    fclose(fp);
}

void loadContacts(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        /* No existing file yet, start fresh */
        return;
    }
    fread(&nextId, sizeof(int), 1, fp);
    fread(&contactCount, sizeof(int), 1, fp);
    fread(contacts, sizeof(Contact), contactCount, fp);
    fclose(fp);
}

/* ---------- Core Features ---------- */

void addContact(void) {
    if (contactCount >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }

    Contact c;
    c.id = nextId++;

    printf("\n--- Add New Contact ---\n");

    printf("Name : ");
    readLine(c.name, NAME_LEN);

    printf("Phone: ");
    readLine(c.phone, PHONE_LEN);

    printf("Email: ");
    readLine(c.email, EMAIL_LEN);

    contacts[contactCount++] = c;
    saveContacts();

    printf("\nContact added successfully! (ID: %d)\n", c.id);
}

void listContacts(void) {
    if (contactCount == 0) {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n%-5s %-20s %-15s %-25s\n", "ID", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");
    for (int i = 0; i < contactCount; i++) {
        printf("%-5d %-20s %-15s %-25s\n",
               contacts[i].id, contacts[i].name,
               contacts[i].phone, contacts[i].email);
    }
    printf("\nTotal contacts: %d\n", contactCount);
}

/* Returns index of contact matching name/phone substring, or -1 if not found.
   Prints all matches and returns the index of the LAST match shown
   (useful when caller wants a single match to act on). */
int searchContacts(void) {
    char query[NAME_LEN];
    char queryLower[NAME_LEN];
    char fieldLower[NAME_LEN];

    printf("\nEnter name or phone number to search: ");
    readLine(query, NAME_LEN);
    toLowerStr(queryLower, query);

    int found = 0;
    int lastMatch = -1;

    printf("\n%-5s %-20s %-15s %-25s\n", "ID", "Name", "Phone", "Email");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < contactCount; i++) {
        toLowerStr(fieldLower, contacts[i].name);
        if (strstr(fieldLower, queryLower) != NULL ||
            strstr(contacts[i].phone, query) != NULL) {
            printf("%-5d %-20s %-15s %-25s\n",
                   contacts[i].id, contacts[i].name,
                   contacts[i].phone, contacts[i].email);
            found++;
            lastMatch = i;
        }
    }

    if (!found) {
        printf("No matching contacts found.\n");
        return -1;
    }

    printf("\n%d match(es) found.\n", found);
    return lastMatch;
}

/* Finds a contact index by its unique ID */
int findIndexById(int id) {
    for (int i = 0; i < contactCount; i++) {
        if (contacts[i].id == id) {
            return i;
        }
    }
    return -1;
}

void updateContact(void) {
    if (contactCount == 0) {
        printf("\nNo contacts to update.\n");
        return;
    }

    listContacts();

    int id;
    printf("\nEnter the ID of the contact to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findIndexById(id);
    if (idx == -1) {
        printf("Contact with ID %d not found.\n", id);
        return;
    }

    printf("\nLeave a field blank to keep its current value.\n");

    char buffer[NAME_LEN];

    printf("Name [%s]: ", contacts[idx].name);
    readLine(buffer, NAME_LEN);
    if (strlen(buffer) > 0) strcpy(contacts[idx].name, buffer);

    printf("Phone [%s]: ", contacts[idx].phone);
    readLine(buffer, PHONE_LEN);
    if (strlen(buffer) > 0) strcpy(contacts[idx].phone, buffer);

    printf("Email [%s]: ", contacts[idx].email);
    readLine(buffer, EMAIL_LEN);
    if (strlen(buffer) > 0) strcpy(contacts[idx].email, buffer);

    saveContacts();
    printf("\nContact updated successfully!\n");
}

void deleteContact(void) {
    if (contactCount == 0) {
        printf("\nNo contacts to delete.\n");
        return;
    }

    listContacts();

    int id;
    printf("\nEnter the ID of the contact to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    int idx = findIndexById(id);
    if (idx == -1) {
        printf("Contact with ID %d not found.\n", id);
        return;
    }

    char confirm;
    printf("Are you sure you want to delete '%s'? (y/n): ", contacts[idx].name);
    scanf(" %c", &confirm);
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        /* Shift all later contacts left by one to fill the gap */
        for (int i = idx; i < contactCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactCount--;
        saveContacts();
        printf("Contact deleted successfully!\n");
    } else {
        printf("Deletion cancelled.\n");
    }
}

/* ---------- Menu ---------- */

void printMenu(void) {
    printf("\n========== CONTACT MANAGEMENT SYSTEM ==========\n");
    printf("1. Add Contact\n");
    printf("2. View All Contacts\n");
    printf("3. Search Contact\n");
    printf("4. Update Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Exit\n");
    printf("=================================================\n");
    printf("Enter your choice: ");
}

int main(void) {
    loadContacts();

    int choice;
    int running = 1;

    while (running) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            /* Invalid (non-numeric) input */
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addContact();    break;
            case 2: listContacts();  break;
            case 3: searchContacts(); break;
            case 4: updateContact(); break;
            case 5: deleteContact(); break;
            case 6:
                printf("\nSaving and exiting. Goodbye!\n");
                saveContacts();
                running = 0;
                break;
            default:
                printf("Invalid choice. Please select 1-6.\n");
        }
    }

    return 0;
}