/*
 * ================================================================
 *   LIBRARY MANAGEMENT SYSTEM IN C
 * ================================================================
 *
 *  Two modules — BOOKS and MEMBERS — each with full CRUD.
 *  A separate TRANSACTION log tracks every issue and return.
 *
 *  Features:
 *  ── Book Management ──────────────────────────────────────
 *   1.  Add Book
 *   2.  Display All Books
 *   3.  Search Book (by ID / Title / Author)
 *   4.  Update Book Details
 *   5.  Delete Book
 *
 *  ── Member Management ────────────────────────────────────
 *   6.  Add Member
 *   7.  Display All Members
 *   8.  Search Member
 *   9.  Update Member Details
 *  10.  Delete Member
 *
 *  ── Transactions ─────────────────────────────────────────
 *  11.  Issue Book   (member borrows a book)
 *  12.  Return Book  (book returned; fine if overdue)
 *  13.  View All Transactions
 *  14.  View Member's Borrowed Books
 *  15.  View Overdue Books
 *
 *  ── Reports & Utilities ──────────────────────────────────
 *  16.  Library Report (totals, availability, fines)
 *  17.  Save All Data to Files
 *  18.  Load All Data from Files
 *  19.  Exit
 *
 *  Files created:
 *    books.dat       — book records (CSV)
 *    members.dat     — member records (CSV)
 *    transactions.dat— issue/return log (CSV)
 *
 *  Fine rate: Rs. 2 per day after the due date (7-day loan period)
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_BOOKS        300
#define MAX_MEMBERS      200
#define MAX_TRANSACTIONS 1000
#define TITLE_LEN         80
#define AUTHOR_LEN        50
#define NAME_LEN          50
#define PHONE_LEN         15
#define EMAIL_LEN         50
#define GENRE_LEN         30
#define LOAN_DAYS          7      /* How many days a member can keep a book */
#define FINE_PER_DAY       2.0   /* Fine in Rs. per overdue day             */
#define BOOKS_FILE        "books.dat"
#define MEMBERS_FILE      "members.dat"
#define TRANS_FILE        "transactions.dat"

/* ================================================================
 *  DATA STRUCTURES
 * ================================================================ */

/* ── Book ───────────────────────────────────────────────────── */
typedef struct {
    int  id;
    char title[TITLE_LEN];
    char author[AUTHOR_LEN];
    char genre[GENRE_LEN];
    int  totalCopies;      /* Total copies owned by library      */
    int  availCopies;      /* Copies currently on the shelf      */
    int  year;             /* Publication year                   */
} Book;

/* ── Member ─────────────────────────────────────────────────── */
typedef struct {
    int  id;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    int  booksIssued;      /* How many books currently borrowed  */
    int  maxBooks;         /* Max allowed (default 3)            */
} Member;

/* ── Transaction ────────────────────────────────────────────── */
/* STATUS: 'I' = Issued, 'R' = Returned                         */
typedef struct {
    int    txnID;
    int    bookID;
    int    memberID;
    char   bookTitle[TITLE_LEN];
    char   memberName[NAME_LEN];
    /* Dates stored as integers YYYYMMDD for easy diff arithmetic */
    long   issueDate;
    long   dueDate;
    long   returnDate;     /* 0 if not yet returned              */
    char   status;         /* 'I' = Issued, 'R' = Returned      */
    double fine;           /* Fine collected on return (0 if on time) */
} Transaction;

/* ── Global arrays ──────────────────────────────────────────── */
Book        books[MAX_BOOKS];
Member      members[MAX_MEMBERS];
Transaction transactions[MAX_TRANSACTIONS];

int bookCount  = 0;
int memberCount = 0;
int txnCount   = 0;
int nextBookID   = 1001;
int nextMemberID = 2001;
int nextTxnID    = 3001;

/* ================================================================
 *  HELPER FUNCTIONS
 * ================================================================ */

/* Clears leftover characters from the input buffer */
void flushInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Reads a full line safely (handles spaces) */
void readLine(char str[], int maxLen)
{
    int i = 0, c;
    while (i < maxLen - 1 && (c = getchar()) != '\n' && c != EOF)
        str[i++] = (char)c;
    str[i] = '\0';
}

/* Case-insensitive substring check */
int containsStr(const char *hay, const char *needle)
{
    char h[TITLE_LEN * 2] = {0};
    char n[TITLE_LEN * 2] = {0};
    int  i;
    for (i = 0; hay[i]; i++)
        h[i] = (hay[i] >= 'A' && hay[i] <= 'Z') ? hay[i] + 32 : hay[i];
    for (i = 0; needle[i]; i++)
        n[i] = (needle[i] >= 'A' && needle[i] <= 'Z') ? needle[i] + 32 : needle[i];
    return strstr(h, n) != NULL;
}

/* Find book index by ID; -1 if not found */
int findBook(int id)
{
    for (int i = 0; i < bookCount; i++)
        if (books[i].id == id) return i;
    return -1;
}

/* Find member index by ID; -1 if not found */
int findMember(int id)
{
    for (int i = 0; i < memberCount; i++)
        if (members[i].id == id) return i;
    return -1;
}

/* ── Simple date system ──────────────────────────────────────── */
/*
 * We represent dates as long integers: YYYYMMDD
 * e.g. 20240615 means 15 June 2024.
 *
 * getToday() asks the user for today's date (since we have no
 * real-time clock in standard C without OS-specific headers).
 * In a real system you would use time() from <time.h>.
 */
long getToday(void)
{
    int y, m, d;
    printf("Enter today's date (YYYY MM DD): ");
    if (scanf("%d %d %d", &y, &m, &d) != 3) {
        flushInput();
        /* Default fallback date */
        return 20240101L;
    }
    flushInput();
    return (long)y * 10000 + m * 100 + d;
}

/* Add LOAN_DAYS to a YYYYMMDD date (simple; ignores month-end edge cases) */
long addDays(long date, int days)
{
    int y = (int)(date / 10000);
    int m = (int)((date % 10000) / 100);
    int d = (int)(date % 100);

    /* Days-in-month table (ignoring leap years for simplicity) */
    int dim[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (y % 4 == 0) dim[2] = 29;   /* Rough leap-year check */

    d += days;
    while (d > dim[m]) {
        d -= dim[m];
        m++;
        if (m > 12) { m = 1; y++; if (y % 4 == 0) dim[2] = 29; else dim[2] = 28; }
    }
    return (long)y * 10000 + m * 100 + d;
}

/* Calculate difference in days between two YYYYMMDD dates (date2 - date1) */
long dateDiff(long date1, long date2)
{
    /*
     * Convert each date to an approximate day-count from a base point.
     * Accurate enough for fine calculation (±1 day on month boundaries).
     */
    int y1 = (int)(date1/10000), m1 = (int)((date1%10000)/100), d1 = (int)(date1%100);
    int y2 = (int)(date2/10000), m2 = (int)((date2%10000)/100), d2 = (int)(date2%100);
    long days1 = y1*365L + y1/4 + m1*30 + d1;
    long days2 = y2*365L + y2/4 + m2*30 + d2;
    return days2 - days1;
}

void formatDate(long date, char *buf)
{
    int y = (int)(date/10000), m = (int)((date%10000)/100), d = (int)(date%100);
    sprintf(buf, "%02d/%02d/%04d", d, m, y);
}

/* ── Print helpers ───────────────────────────────────────────── */
void printLine(void) { printf("%-70s\n", "----------------------------------------------------------------------"); }

void printBookHeader(void)
{
    printLine();
    printf("%-6s %-30s %-20s %-12s %5s %5s %4s\n",
           "ID", "Title", "Author", "Genre", "Total", "Avail", "Year");
    printLine();
}

void printBook(const Book *b)
{
    printf("%-6d %-30s %-20s %-12s %5d %5d %4d\n",
           b->id, b->title, b->author, b->genre,
           b->totalCopies, b->availCopies, b->year);
}

void printMemberHeader(void)
{
    printLine();
    printf("%-6s %-25s %-15s %-25s %7s %7s\n",
           "ID", "Name", "Phone", "Email", "Issued", "MaxBks");
    printLine();
}

void printMember(const Member *m)
{
    printf("%-6d %-25s %-15s %-25s %7d %7d\n",
           m->id, m->name, m->phone, m->email,
           m->booksIssued, m->maxBooks);
}

/* ================================================================
 *  BOOK MANAGEMENT
 * ================================================================ */

/* ── 1. Add Book ─────────────────────────────────────────────── */
void addBook(void)
{
    if (bookCount >= MAX_BOOKS) {
        printf("[!] Book catalog is full.\n"); return;
    }

    Book b;
    b.id = nextBookID++;

    printf("\n--- ADD BOOK (ID: %d) ---\n", b.id);

    printf("Title         : "); readLine(b.title, TITLE_LEN);
    if (b.title[0] == '\0') { printf("[!] Title cannot be empty.\n"); nextBookID--; return; }

    printf("Author        : "); readLine(b.author, AUTHOR_LEN);
    if (b.author[0] == '\0') strcpy(b.author, "Unknown");

    printf("Genre         : "); readLine(b.genre, GENRE_LEN);
    if (b.genre[0] == '\0') strcpy(b.genre, "General");

    printf("Year Published: ");
    if (scanf("%d", &b.year) != 1) { flushInput(); b.year = 2000; } else flushInput();

    printf("Total Copies  : ");
    if (scanf("%d", &b.totalCopies) != 1 || b.totalCopies <= 0) {
        printf("[!] Invalid copies.\n"); flushInput(); nextBookID--; return;
    }
    flushInput();

    b.availCopies = b.totalCopies;   /* All copies available initially */

    books[bookCount++] = b;
    printf("[+] Book '%s' added with ID %d.\n", b.title, b.id);
}

/* ── 2. Display All Books ────────────────────────────────────── */
void displayBooks(void)
{
    if (bookCount == 0) { printf("[!] No books in catalog.\n"); return; }
    printf("\n=== ALL BOOKS (%d) ===\n", bookCount);
    printBookHeader();
    for (int i = 0; i < bookCount; i++) printBook(&books[i]);
    printLine();
}

/* ── 3. Search Book ──────────────────────────────────────────── */
void searchBook(void)
{
    if (bookCount == 0) { printf("[!] No books.\n"); return; }

    printf("Search by: 1.ID  2.Title  3.Author  3.Genre : ");
    int opt; scanf("%d", &opt); flushInput();

    if (opt == 1) {
        printf("Enter Book ID: "); int id; scanf("%d", &id); flushInput();
        int idx = findBook(id);
        if (idx == -1) { printf("[-] Not found.\n"); return; }
        printBookHeader(); printBook(&books[idx]); printLine();
    } else {
        char kw[TITLE_LEN];
        printf("Enter keyword: "); readLine(kw, TITLE_LEN);
        int found = 0;
        printBookHeader();
        for (int i = 0; i < bookCount; i++) {
            if (containsStr(books[i].title,  kw) ||
                containsStr(books[i].author, kw) ||
                containsStr(books[i].genre,  kw)) {
                printBook(&books[i]); found++;
            }
        }
        printLine();
        printf("[%s] %d match(es).\n", found ? "+" : "-", found);
    }
}

/* ── 4. Update Book ──────────────────────────────────────────── */
void updateBook(void)
{
    printf("Enter Book ID to update: "); int id; scanf("%d", &id); flushInput();
    int idx = findBook(id);
    if (idx == -1) { printf("[-] Book %d not found.\n", id); return; }

    Book *b = &books[idx];
    char buf[TITLE_LEN];

    printf("Press Enter to keep current value.\n");
    printf("Title  [%s]: ", b->title);  readLine(buf, TITLE_LEN);  if (buf[0]) strcpy(b->title,  buf);
    printf("Author [%s]: ", b->author); readLine(buf, AUTHOR_LEN); if (buf[0]) strcpy(b->author, buf);
    printf("Genre  [%s]: ", b->genre);  readLine(buf, GENRE_LEN);  if (buf[0]) strcpy(b->genre,  buf);
    printf("Year   [%d]: ", b->year);   readLine(buf, 10);          if (buf[0]) b->year = atoi(buf);

    printf("[+] Book ID %d updated.\n", id);
}

/* ── 5. Delete Book ──────────────────────────────────────────── */
void deleteBook(void)
{
    printf("Enter Book ID to delete: "); int id; scanf("%d", &id); flushInput();
    int idx = findBook(id);
    if (idx == -1) { printf("[-] Not found.\n"); return; }

    if (books[idx].availCopies < books[idx].totalCopies) {
        printf("[!] Some copies of this book are currently issued. Cannot delete.\n");
        return;
    }

    printf("Delete '%s'? (y/n): ", books[idx].title);
    char c; scanf(" %c", &c); flushInput();
    if (c != 'y' && c != 'Y') { printf("[!] Cancelled.\n"); return; }

    for (int i = idx; i < bookCount - 1; i++) books[i] = books[i+1];
    bookCount--;
    printf("[+] Book deleted.\n");
}

/* ================================================================
 *  MEMBER MANAGEMENT
 * ================================================================ */

/* ── 6. Add Member ───────────────────────────────────────────── */
void addMember(void)
{
    if (memberCount >= MAX_MEMBERS) { printf("[!] Member list full.\n"); return; }

    Member m;
    m.id = nextMemberID++;
    m.booksIssued = 0;
    m.maxBooks    = 3;   /* Default borrow limit */

    printf("\n--- ADD MEMBER (ID: %d) ---\n", m.id);

    printf("Full Name   : "); readLine(m.name, NAME_LEN);
    if (m.name[0] == '\0') { printf("[!] Name required.\n"); nextMemberID--; return; }

    printf("Phone       : "); readLine(m.phone, PHONE_LEN);
    printf("Email       : "); readLine(m.email, EMAIL_LEN);

    printf("Max Books Allowed [3]: ");
    char buf[10]; readLine(buf, 10);
    m.maxBooks = (buf[0]) ? atoi(buf) : 3;
    if (m.maxBooks < 1 || m.maxBooks > 10) m.maxBooks = 3;

    members[memberCount++] = m;
    printf("[+] Member '%s' added with ID %d.\n", m.name, m.id);
}

/* ── 7. Display All Members ──────────────────────────────────── */
void displayMembers(void)
{
    if (memberCount == 0) { printf("[!] No members.\n"); return; }
    printf("\n=== ALL MEMBERS (%d) ===\n", memberCount);
    printMemberHeader();
    for (int i = 0; i < memberCount; i++) printMember(&members[i]);
    printLine();
}

/* ── 8. Search Member ────────────────────────────────────────── */
void searchMember(void)
{
    if (memberCount == 0) { printf("[!] No members.\n"); return; }

    printf("Search by: 1.ID  2.Name  3.Phone : ");
    int opt; scanf("%d", &opt); flushInput();

    if (opt == 1) {
        printf("Member ID: "); int id; scanf("%d", &id); flushInput();
        int idx = findMember(id);
        if (idx == -1) { printf("[-] Not found.\n"); return; }
        printMemberHeader(); printMember(&members[idx]); printLine();
    } else {
        char kw[NAME_LEN]; printf("Keyword: "); readLine(kw, NAME_LEN);
        int found = 0; printMemberHeader();
        for (int i = 0; i < memberCount; i++) {
            if (containsStr(members[i].name, kw) ||
                containsStr(members[i].phone, kw) ||
                containsStr(members[i].email, kw)) {
                printMember(&members[i]); found++;
            }
        }
        printLine();
        printf("[%s] %d match(es).\n", found ? "+" : "-", found);
    }
}

/* ── 9. Update Member ────────────────────────────────────────── */
void updateMember(void)
{
    printf("Member ID to update: "); int id; scanf("%d", &id); flushInput();
    int idx = findMember(id);
    if (idx == -1) { printf("[-] Not found.\n"); return; }

    Member *m = &members[idx];
    char buf[EMAIL_LEN];

    printf("Press Enter to keep current.\n");
    printf("Name  [%s]: ", m->name);  readLine(buf, NAME_LEN);  if (buf[0]) strcpy(m->name,  buf);
    printf("Phone [%s]: ", m->phone); readLine(buf, PHONE_LEN); if (buf[0]) strcpy(m->phone, buf);
    printf("Email [%s]: ", m->email); readLine(buf, EMAIL_LEN); if (buf[0]) strcpy(m->email, buf);
    printf("Max Books [%d]: ", m->maxBooks); readLine(buf, 5);
    if (buf[0]) { int mb = atoi(buf); if (mb >= 1 && mb <= 10) m->maxBooks = mb; }

    printf("[+] Member ID %d updated.\n", id);
}

/* ── 10. Delete Member ───────────────────────────────────────── */
void deleteMember(void)
{
    printf("Member ID to delete: "); int id; scanf("%d", &id); flushInput();
    int idx = findMember(id);
    if (idx == -1) { printf("[-] Not found.\n"); return; }

    if (members[idx].booksIssued > 0) {
        printf("[!] Member has %d book(s) not yet returned. Cannot delete.\n",
               members[idx].booksIssued);
        return;
    }

    printf("Delete member '%s'? (y/n): ", members[idx].name);
    char c; scanf(" %c", &c); flushInput();
    if (c != 'y' && c != 'Y') { printf("[!] Cancelled.\n"); return; }

    for (int i = idx; i < memberCount - 1; i++) members[i] = members[i+1];
    memberCount--;
    printf("[+] Member deleted.\n");
}

/* ================================================================
 *  TRANSACTIONS
 * ================================================================ */

/* ── 11. Issue Book ──────────────────────────────────────────── */
void issueBook(void)
{
    if (txnCount >= MAX_TRANSACTIONS) { printf("[!] Transaction log full.\n"); return; }

    printf("\n--- ISSUE BOOK ---\n");

    printf("Member ID : "); int mid; scanf("%d", &mid); flushInput();
    int mi = findMember(mid);
    if (mi == -1) { printf("[-] Member %d not found.\n", mid); return; }

    if (members[mi].booksIssued >= members[mi].maxBooks) {
        printf("[!] %s has reached their borrow limit (%d books).\n",
               members[mi].name, members[mi].maxBooks);
        return;
    }

    printf("Book ID   : "); int bid; scanf("%d", &bid); flushInput();
    int bi = findBook(bid);
    if (bi == -1) { printf("[-] Book %d not found.\n", bid); return; }

    if (books[bi].availCopies <= 0) {
        printf("[!] No available copies of '%s'.\n", books[bi].title);
        return;
    }

    /* Check member hasn't already borrowed the same book */
    for (int i = 0; i < txnCount; i++) {
        if (transactions[i].bookID   == bid &&
            transactions[i].memberID == mid &&
            transactions[i].status   == 'I') {
            printf("[!] %s already has '%s' issued.\n",
                   members[mi].name, books[bi].title);
            return;
        }
    }

    long today = getToday();

    Transaction t;
    t.txnID      = nextTxnID++;
    t.bookID     = bid;
    t.memberID   = mid;
    strcpy(t.bookTitle,   books[bi].title);
    strcpy(t.memberName,  members[mi].name);
    t.issueDate  = today;
    t.dueDate    = addDays(today, LOAN_DAYS);
    t.returnDate = 0;
    t.status     = 'I';
    t.fine       = 0.0;

    /* Update stock and member count */
    books[bi].availCopies--;
    members[mi].booksIssued++;

    transactions[txnCount++] = t;

    char issueBuf[20], dueBuf[20];
    formatDate(t.issueDate, issueBuf);
    formatDate(t.dueDate,   dueBuf);

    printf("\n[+] Book Issued Successfully!\n");
    printf("    Transaction ID : %d\n", t.txnID);
    printf("    Book           : %s\n", t.bookTitle);
    printf("    Member         : %s\n", t.memberName);
    printf("    Issue Date     : %s\n", issueBuf);
    printf("    Due Date       : %s  (return within %d days)\n", dueBuf, LOAN_DAYS);
}

/* ── 12. Return Book ─────────────────────────────────────────── */
void returnBook(void)
{
    printf("\n--- RETURN BOOK ---\n");
    printf("Transaction ID (or 0 to search by Member+Book ID): ");
    int tid; scanf("%d", &tid); flushInput();

    int idx = -1;

    if (tid != 0) {
        /* Search by transaction ID */
        for (int i = 0; i < txnCount; i++) {
            if (transactions[i].txnID == tid && transactions[i].status == 'I') {
                idx = i; break;
            }
        }
    } else {
        /* Search by member ID + book ID */
        printf("Member ID: "); int mid; scanf("%d", &mid); flushInput();
        printf("Book ID  : "); int bid; scanf("%d", &bid); flushInput();
        for (int i = 0; i < txnCount; i++) {
            if (transactions[i].memberID == mid &&
                transactions[i].bookID   == bid &&
                transactions[i].status   == 'I') {
                idx = i; break;
            }
        }
    }

    if (idx == -1) {
        printf("[-] No active issue record found.\n"); return;
    }

    Transaction *t = &transactions[idx];
    long today = getToday();
    t->returnDate = today;
    t->status     = 'R';

    /* Calculate fine if overdue */
    long overdue = dateDiff(t->dueDate, today);
    if (overdue > 0) {
        t->fine = overdue * FINE_PER_DAY;
    } else {
        t->fine = 0.0;
        overdue = 0;
    }

    /* Restore book availability and member count */
    int bi = findBook(t->bookID);
    int mi = findMember(t->memberID);
    if (bi != -1) books[bi].availCopies++;
    if (mi != -1 && members[mi].booksIssued > 0) members[mi].booksIssued--;

    char retBuf[20], dueBuf[20];
    formatDate(today,       retBuf);
    formatDate(t->dueDate,  dueBuf);

    printf("\n[+] Book Returned Successfully!\n");
    printf("    Book        : %s\n", t->bookTitle);
    printf("    Member      : %s\n", t->memberName);
    printf("    Due Date    : %s\n", dueBuf);
    printf("    Return Date : %s\n", retBuf);

    if (t->fine > 0.0)
        printf("    [FINE] Overdue by %ld day(s). Fine = Rs. %.2f\n",
               overdue, t->fine);
    else
        printf("    [OK]   Returned on time. No fine.\n");
}

/* ── 13. View All Transactions ───────────────────────────────── */
void viewTransactions(void)
{
    if (txnCount == 0) { printf("[!] No transactions yet.\n"); return; }

    printf("\n=== ALL TRANSACTIONS (%d) ===\n", txnCount);
    printLine();
    printf("%-6s %-6s %-6s %-28s %-20s %-12s %-12s %s\n",
           "TxnID", "BkID", "MbID", "Book Title", "Member",
           "IssueDate", "DueDate", "Status");
    printLine();

    for (int i = 0; i < txnCount; i++) {
        Transaction *t = &transactions[i];
        char id[20], dd[20];
        formatDate(t->issueDate, id);
        formatDate(t->dueDate,   dd);
        printf("%-6d %-6d %-6d %-28s %-20s %-12s %-12s %c  Fine:%.2f\n",
               t->txnID, t->bookID, t->memberID,
               t->bookTitle, t->memberName, id, dd,
               t->status, t->fine);
    }
    printLine();
}

/* ── 14. Member's Borrowed Books ─────────────────────────────── */
void memberBooks(void)
{
    printf("Member ID: "); int mid; scanf("%d", &mid); flushInput();
    int mi = findMember(mid);
    if (mi == -1) { printf("[-] Member not found.\n"); return; }

    printf("\nBooks currently issued to '%s':\n", members[mi].name);
    printLine();
    int found = 0;
    for (int i = 0; i < txnCount; i++) {
        if (transactions[i].memberID == mid && transactions[i].status == 'I') {
            char id[20], dd[20];
            formatDate(transactions[i].issueDate, id);
            formatDate(transactions[i].dueDate,   dd);
            printf("  TxnID:%-5d  Book:%-6d  %-30s  Issued:%s  Due:%s\n",
                   transactions[i].txnID, transactions[i].bookID,
                   transactions[i].bookTitle, id, dd);
            found++;
        }
    }
    printLine();
    if (!found) printf("[+] No books currently issued to this member.\n");
}

/* ── 15. Overdue Books ───────────────────────────────────────── */
void overdueBooks(void)
{
    long today = getToday();
    printf("\n=== OVERDUE BOOKS ===\n");
    printLine();
    int found = 0;

    for (int i = 0; i < txnCount; i++) {
        Transaction *t = &transactions[i];
        if (t->status == 'I') {
            long overdue = dateDiff(t->dueDate, today);
            if (overdue > 0) {
                char dd[20];
                formatDate(t->dueDate, dd);
                double fine = overdue * FINE_PER_DAY;
                printf("  TxnID:%-5d  Member:%-6d %-20s  Book:%-6d %-25s  Overdue:%ld day(s)  Fine:Rs.%.2f\n",
                       t->txnID, t->memberID, t->memberName,
                       t->bookID, t->bookTitle, overdue, fine);
                found++;
            }
        }
    }
    printLine();
    if (!found) printf("[+] No overdue books today.\n");
    else        printf("[!] %d overdue book(s) found.\n", found);
}

/* ================================================================
 *  REPORTS
 * ================================================================ */
void libraryReport(void)
{
    int  totalBooks     = 0;
    int  availableBooks = 0;
    int  issuedBooks    = 0;
    int  activeIssues   = 0;
    double totalFines   = 0.0;

    for (int i = 0; i < bookCount; i++) {
        totalBooks     += books[i].totalCopies;
        availableBooks += books[i].availCopies;
        issuedBooks    += books[i].totalCopies - books[i].availCopies;
    }
    for (int i = 0; i < txnCount; i++) {
        if (transactions[i].status == 'I') activeIssues++;
        totalFines += transactions[i].fine;
    }

    printf("\n========== LIBRARY REPORT ==========\n");
    printf("  Unique Book Titles  : %d\n",     bookCount);
    printf("  Total Book Copies   : %d\n",     totalBooks);
    printf("  Available Copies    : %d\n",     availableBooks);
    printf("  Issued Copies       : %d\n",     issuedBooks);
    printf("  Total Members       : %d\n",     memberCount);
    printf("  Active Issues       : %d\n",     activeIssues);
    printf("  Total Transactions  : %d\n",     txnCount);
    printf("  Total Fines Collected: Rs. %.2f\n", totalFines);
    printf("=====================================\n");
}

/* ================================================================
 *  FILE I/O
 * ================================================================ */
void saveData(void)
{
    /* ── Save books ─────────────────────────────────────────── */
    FILE *fp = fopen(BOOKS_FILE, "w");
    if (fp) {
        fprintf(fp, "ID,Title,Author,Genre,Total,Avail,Year\n");
        for (int i = 0; i < bookCount; i++) {
            Book *b = &books[i];
            fprintf(fp, "%d,%s,%s,%s,%d,%d,%d\n",
                    b->id, b->title, b->author, b->genre,
                    b->totalCopies, b->availCopies, b->year);
        }
        fprintf(fp, "#NEXTID,%d\n", nextBookID);
        fclose(fp);
    }

    /* ── Save members ───────────────────────────────────────── */
    fp = fopen(MEMBERS_FILE, "w");
    if (fp) {
        fprintf(fp, "ID,Name,Phone,Email,Issued,MaxBooks\n");
        for (int i = 0; i < memberCount; i++) {
            Member *m = &members[i];
            fprintf(fp, "%d,%s,%s,%s,%d,%d\n",
                    m->id, m->name, m->phone, m->email,
                    m->booksIssued, m->maxBooks);
        }
        fprintf(fp, "#NEXTID,%d\n", nextMemberID);
        fclose(fp);
    }

    /* ── Save transactions ──────────────────────────────────── */
    fp = fopen(TRANS_FILE, "w");
    if (fp) {
        fprintf(fp, "TxnID,BookID,MemberID,BookTitle,MemberName,IssueDate,DueDate,ReturnDate,Status,Fine\n");
        for (int i = 0; i < txnCount; i++) {
            Transaction *t = &transactions[i];
            fprintf(fp, "%d,%d,%d,%s,%s,%ld,%ld,%ld,%c,%.2f\n",
                    t->txnID, t->bookID, t->memberID,
                    t->bookTitle, t->memberName,
                    t->issueDate, t->dueDate, t->returnDate,
                    t->status, t->fine);
        }
        fprintf(fp, "#NEXTID,%d\n", nextTxnID);
        fclose(fp);
    }

    printf("[+] All data saved (Books:%d  Members:%d  Txns:%d).\n",
           bookCount, memberCount, txnCount);
}

void loadData(void)
{
    char line[512];

    /* ── Load books ─────────────────────────────────────────── */
    FILE *fp = fopen(BOOKS_FILE, "r");
    if (fp) {
        bookCount = 0;
        fgets(line, sizeof(line), fp);   /* Skip header */
        while (fgets(line, sizeof(line), fp)) {
            if (line[0] == '#') {
                sscanf(line, "#NEXTID,%d", &nextBookID); continue;
            }
            if (bookCount >= MAX_BOOKS) break;
            Book b;
            if (sscanf(line, "%d,%79[^,],%49[^,],%29[^,],%d,%d,%d",
                       &b.id, b.title, b.author, b.genre,
                       &b.totalCopies, &b.availCopies, &b.year) == 7)
                books[bookCount++] = b;
        }
        fclose(fp);
        printf("[+] Loaded %d book(s).\n", bookCount);
    }

    /* ── Load members ───────────────────────────────────────── */
    fp = fopen(MEMBERS_FILE, "r");
    if (fp) {
        memberCount = 0;
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp)) {
            if (line[0] == '#') {
                sscanf(line, "#NEXTID,%d", &nextMemberID); continue;
            }
            if (memberCount >= MAX_MEMBERS) break;
            Member m;
            if (sscanf(line, "%d,%49[^,],%14[^,],%49[^,],%d,%d",
                       &m.id, m.name, m.phone, m.email,
                       &m.booksIssued, &m.maxBooks) == 6)
                members[memberCount++] = m;
        }
        fclose(fp);
        printf("[+] Loaded %d member(s).\n", memberCount);
    }

    /* ── Load transactions ──────────────────────────────────── */
    fp = fopen(TRANS_FILE, "r");
    if (fp) {
        txnCount = 0;
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp)) {
            if (line[0] == '#') {
                sscanf(line, "#NEXTID,%d", &nextTxnID); continue;
            }
            if (txnCount >= MAX_TRANSACTIONS) break;
            Transaction t;
            char statusChar;
            if (sscanf(line, "%d,%d,%d,%79[^,],%49[^,],%ld,%ld,%ld,%c,%lf",
                       &t.txnID, &t.bookID, &t.memberID,
                       t.bookTitle, t.memberName,
                       &t.issueDate, &t.dueDate, &t.returnDate,
                       &statusChar, &t.fine) == 10) {
                t.status = statusChar;
                transactions[txnCount++] = t;
            }
        }
        fclose(fp);
        printf("[+] Loaded %d transaction(s).\n", txnCount);
    }
}

/* ================================================================
 *  MENU
 * ================================================================ */
void printMenu(void)
{
    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║       LIBRARY MANAGEMENT SYSTEM          ║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║  BOOK MANAGEMENT                         ║\n");
    printf("║   1. Add Book          2. Display Books  ║\n");
    printf("║   3. Search Book       4. Update Book    ║\n");
    printf("║   5. Delete Book                         ║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║  MEMBER MANAGEMENT                       ║\n");
    printf("║   6. Add Member        7. Display Members║\n");
    printf("║   8. Search Member     9. Update Member  ║\n");
    printf("║  10. Delete Member                       ║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║  TRANSACTIONS                            ║\n");
    printf("║  11. Issue Book       12. Return Book    ║\n");
    printf("║  13. All Transactions 14. Member's Books ║\n");
    printf("║  15. Overdue Books                       ║\n");
    printf("╠══════════════════════════════════════════╣\n");
    printf("║  REPORTS & UTILITIES                     ║\n");
    printf("║  16. Library Report   17. Save Data      ║\n");
    printf("║  18. Load Data        19. Exit           ║\n");
    printf("╚══════════════════════════════════════════╝\n");
    printf("  Books:%-4d  Members:%-4d  Transactions:%-4d\n",
           bookCount, memberCount, txnCount);
    printf("Enter choice (1-19): ");
}

/* ================================================================
 *  MAIN
 * ================================================================ */
int main(void)
{
    int choice;

    printf("\n╔══════════════════════════════════════════╗\n");
    printf("║     LIBRARY MANAGEMENT SYSTEM  v1.0     ║\n");
    printf("║        C Programming Project             ║\n");
    printf("╚══════════════════════════════════════════╝\n");

    /* Auto-load on startup */
    printf("\n[*] Loading saved data...\n");
    loadData();

    do {
        printMenu();

        /* Guard against non-integer input */
        if (scanf("%d", &choice) != 1) {
            flushInput();
            printf("[!] Enter a number 1-19.\n");
            choice = 0;
            continue;
        }
        flushInput();
        printf("\n");

        switch (choice)
        {
            case  1: addBook();          break;
            case  2: displayBooks();     break;
            case  3: searchBook();       break;
            case  4: updateBook();       break;
            case  5: deleteBook();       break;
            case  6: addMember();        break;
            case  7: displayMembers();   break;
            case  8: searchMember();     break;
            case  9: updateMember();     break;
            case 10: deleteMember();     break;
            case 11: issueBook();        break;
            case 12: returnBook();       break;
            case 13: viewTransactions(); break;
            case 14: memberBooks();      break;
            case 15: overdueBooks();     break;
            case 16: libraryReport();    break;
            case 17: saveData();         break;
            case 18: loadData();         break;
            case 19:
                printf("[*] Auto-saving before exit...\n");
                saveData();
                printf("Goodbye! Happy Reading!\n");
                break;
            default:
                printf("[!] Invalid choice. Enter 1-19.\n");
        }

    } while (choice != 19);

    return 0;
}