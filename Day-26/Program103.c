#include <stdio.h>

/* ============================================================
   ATM SIMULATION  -  User Friendly, Minimal stdlib
   Features: Balance Inquiry, Deposit, Withdrawal, PIN Change
   ============================================================ */

/* ---------- constants ---------- */
#define MAX_ACCOUNTS     5
#define PIN_LENGTH       4
#define MAX_NAME_LEN     40
#define MAX_WRONG_TRIES  3

/* ---------- custom string helpers (no string.h) ---------- */

/* returns length of string */
int str_len(const char *s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

/* copies src into dst */
void str_copy(char *dst, const char *src) {
    int i = 0;
    while (src[i] != '\0') { dst[i] = src[i]; i++; }
    dst[i] = '\0';
}

/* returns 1 if two strings are equal, 0 otherwise */
int str_equal(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

/* reads a single line from stdin into buf (max len chars) */
void read_line(char *buf, int max_len) {
    int i = 0;
    char c;
    while (i < max_len - 1) {
        c = getchar();
        if (c == '\n' || c == EOF) break;
        buf[i++] = c;
    }
    buf[i] = '\0';
}

/* reads only digits, returns integer value, -1 on bad input */
int read_int() {
    char buf[20];
    read_line(buf, 20);
    int len = str_len(buf);
    if (len == 0) return -1;
    int val = 0;
    for (int i = 0; i < len; i++) {
        if (buf[i] < '0' || buf[i] > '9') return -1;
        val = val * 10 + (buf[i] - '0');
    }
    return val;
}

/* converts integer to string, writes into buf */
void int_to_str(int n, char *buf) {
    if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    char tmp[20];
    int i = 0;
    while (n > 0) { tmp[i++] = '0' + (n % 10); n /= 10; }
    for (int j = 0; j < i; j++) buf[j] = tmp[i - 1 - j];
    buf[i] = '\0';
}

/* prints integer without printf %d */
void print_int(int n) {
    char buf[20];
    int_to_str(n, buf);
    printf("%s", buf);
}

/* ---------- data ---------- */
typedef struct {
    char  name[MAX_NAME_LEN];
    char  account_no[12];
    char  pin[PIN_LENGTH + 1];   /* 4 digits + null */
    int   balance;               /* stored in whole currency units */
} Account;

Account accounts[MAX_ACCOUNTS] = {
    {"Rahul Sharma",   "ACC001", "1234", 15000},
    {"Priya Mehta",    "ACC002", "5678", 42000},
    {"Amit Verma",     "ACC003", "2222", 8500 },
    {"Sneha Gupta",    "ACC004", "9999", 61000},
    {"Ravi Kumar",     "ACC005", "3333", 3200 },
};

/* ---------- display helpers ---------- */
void print_line(char ch, int count) {
    for (int i = 0; i < count; i++) putchar(ch);
    putchar('\n');
}

void print_header(const char *title) {
    putchar('\n');
    print_line('=', 48);
    int len   = str_len(title);
    int pad   = (48 - len) / 2;
    for (int i = 0; i < pad; i++) putchar(' ');
    printf("%s\n", title);
    print_line('=', 48);
}

void print_section(const char *title) {
    putchar('\n');
    printf("  >> %s\n", title);
    print_line('-', 48);
}

void press_enter_to_continue() {
    printf("\n  Press ENTER to return to menu...");
    /* consume any leftover newline then wait */
    getchar();
}

/* ---------- PIN entry (masked with asterisks) ---------- */
void read_pin(char *pin_buf) {
    /* We cannot truly mask in standard C without OS calls,
       so we just read normally and show '*' feedback */
    char c;
    int i = 0;
    printf("  PIN : ");
    while (i < PIN_LENGTH) {
        c = getchar();
        if (c == '\n' || c == EOF) break;
        if (c >= '0' && c <= '9') {
            pin_buf[i++] = c;
            putchar('*');
        }
    }
    /* drain rest of line */
    while (c != '\n' && c != EOF) c = getchar();
    pin_buf[i] = '\0';
    putchar('\n');
}

/* ---------- find account by number ---------- */
int find_account(const char *acc_no) {
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        if (str_equal(accounts[i].account_no, acc_no))
            return i;
    }
    return -1;
}

/* ============================================================
   FEATURE 1 : Balance Inquiry
   ============================================================ */
void show_balance(int idx) {
    print_header("BALANCE INQUIRY");
    printf("\n  Account Holder : %s\n", accounts[idx].name);
    printf("  Account Number : %s\n",  accounts[idx].account_no);
    printf("\n");
    print_line('-', 48);
    printf("  Available Balance :  Rs. ");
    print_int(accounts[idx].balance);
    printf("\n");
    print_line('-', 48);
    press_enter_to_continue();
}

/* ============================================================
   FEATURE 2 : Deposit
   ============================================================ */
void deposit(int idx) {
    print_header("DEPOSIT CASH");
    printf("\n  Account  : %s  (%s)\n",
           accounts[idx].name, accounts[idx].account_no);
    printf("  Current Balance : Rs. ");
    print_int(accounts[idx].balance);
    printf("\n\n");

    int amount;
    while (1) {
        printf("  Enter amount to deposit (Rs.): ");
        amount = read_int();

        if (amount <= 0) {
            printf("  [!] Please enter a valid amount greater than 0.\n");
            continue;
        }
        if (amount % 100 != 0) {
            printf("  [!] Amount must be a multiple of 100 (e.g. 500, 1000).\n");
            continue;
        }
        if (amount > 100000) {
            printf("  [!] Maximum single deposit limit is Rs. 1,00,000.\n");
            continue;
        }
        break;
    }

    accounts[idx].balance += amount;

    putchar('\n');
    print_line('-', 48);
    printf("  Deposited        :  Rs. "); print_int(amount);   printf("\n");
    printf("  Updated Balance  :  Rs. "); print_int(accounts[idx].balance); printf("\n");
    print_line('-', 48);
    printf("  Deposit successful! Thank you.\n");
    press_enter_to_continue();
}

/* ============================================================
   FEATURE 3 : Withdrawal
   ============================================================ */
void withdraw(int idx) {
    print_header("CASH WITHDRAWAL");
    printf("\n  Account  : %s  (%s)\n",
           accounts[idx].name, accounts[idx].account_no);
    printf("  Available Balance : Rs. ");
    print_int(accounts[idx].balance);
    printf("\n\n");

    int amount;
    while (1) {
        printf("  Enter amount to withdraw (Rs.): ");
        amount = read_int();

        if (amount <= 0) {
            printf("  [!] Please enter a valid amount greater than 0.\n");
            continue;
        }
        if (amount % 100 != 0) {
            printf("  [!] ATM dispenses notes of Rs.100 and above.\n"
                   "      Enter a multiple of 100 (e.g. 500, 2000).\n");
            continue;
        }
        if (amount > 20000) {
            printf("  [!] Maximum withdrawal per transaction is Rs. 20,000.\n");
            continue;
        }
        if (amount > accounts[idx].balance) {
            printf("  [!] Insufficient balance.\n"
                   "      Your balance is Rs. ");
            print_int(accounts[idx].balance);
            printf(".\n");
            continue;
        }
        break;
    }

    accounts[idx].balance -= amount;

    putchar('\n');
    print_line('-', 48);
    printf("  Withdrawn        :  Rs. "); print_int(amount);   printf("\n");
    printf("  Remaining Balance:  Rs. "); print_int(accounts[idx].balance); printf("\n");
    print_line('-', 48);
    printf("  Please collect your cash. Have a nice day!\n");
    press_enter_to_continue();
}

/* ============================================================
   FEATURE 4 : PIN Change
   ============================================================ */
void change_pin(int idx) {
    print_header("CHANGE PIN");
    printf("\n  You are changing the PIN for account: %s\n\n",
           accounts[idx].account_no);

    /* confirm current PIN once more */
    char current[PIN_LENGTH + 1];
    printf("  Enter your CURRENT ");
    read_pin(current);
    if (!str_equal(current, accounts[idx].pin)) {
        printf("\n  [!] Incorrect current PIN. Returning to menu.\n");
        press_enter_to_continue();
        return;
    }

    char new_pin[PIN_LENGTH + 1];
    char confirm_pin[PIN_LENGTH + 1];

    printf("  Enter NEW 4-digit ");
    read_pin(new_pin);

    if (str_len(new_pin) != PIN_LENGTH) {
        printf("\n  [!] PIN must be exactly 4 digits.\n");
        press_enter_to_continue();
        return;
    }
    /* reject PINs like 1111, 1234 for safety */
    int all_same = 1;
    for (int i = 1; i < PIN_LENGTH; i++)
        if (new_pin[i] != new_pin[0]) { all_same = 0; break; }
    if (all_same) {
        printf("\n  [!] PIN cannot have all identical digits (e.g. 1111).\n");
        press_enter_to_continue();
        return;
    }
    if (str_equal(new_pin, "1234") || str_equal(new_pin, "0000")) {
        printf("\n  [!] That PIN is too easy to guess. Choose a stronger one.\n");
        press_enter_to_continue();
        return;
    }

    printf("  Confirm NEW ");
    read_pin(confirm_pin);

    if (!str_equal(new_pin, confirm_pin)) {
        printf("\n  [!] PINs do not match. No changes made.\n");
        press_enter_to_continue();
        return;
    }

    str_copy(accounts[idx].pin, new_pin);

    putchar('\n');
    print_line('-', 48);
    printf("  PIN changed successfully!\n");
    printf("  Please remember your new PIN.\n");
    print_line('-', 48);
    press_enter_to_continue();
}

/* ============================================================
   LOGIN  -  account number + PIN with lockout
   ============================================================ */
int login() {
    print_header("WELCOME TO THE ATM");
    printf("\n  Please enter your account details to continue.\n\n");

    char acc_no[12];
    printf("  Account Number : ");
    read_line(acc_no, 12);

    int idx = find_account(acc_no);
    if (idx == -1) {
        printf("\n  [!] Account not found. Please check your account number.\n");
        press_enter_to_continue();
        return -1;
    }

    /* PIN verification with lockout after 3 wrong tries */
    int tries = 0;
    while (tries < MAX_WRONG_TRIES) {
        int remaining = MAX_WRONG_TRIES - tries;
        printf("\n  Attempt %d of %d.\n", tries + 1, MAX_WRONG_TRIES);

        char entered_pin[PIN_LENGTH + 1];
        printf("  Enter your 4-digit ");
        read_pin(entered_pin);

        if (str_equal(entered_pin, accounts[idx].pin)) {
            printf("\n  Login successful! Welcome, %s.\n", accounts[idx].name);
            press_enter_to_continue();
            return idx;
        }

        tries++;
        remaining--;
        if (remaining > 0) {
            printf("  [!] Wrong PIN. You have %d attempt", remaining);
            if (remaining > 1) printf("s");
            printf(" left.\n");
        }
    }

    printf("\n  [!] Too many wrong attempts.\n");
    printf("      Your card has been blocked for security.\n");
    printf("      Please contact your bank branch.\n");
    press_enter_to_continue();
    return -1;
}

/* ============================================================
   ACCOUNT MENU  (shown after successful login)
   ============================================================ */
void account_menu(int idx) {
    int choice;
    while (1) {
        print_header("ATM MAIN MENU");
        printf("\n  Hello, %s!\n\n", accounts[idx].name);
        printf("  1.  Balance Inquiry\n");
        printf("  2.  Deposit Cash\n");
        printf("  3.  Withdraw Cash\n");
        printf("  4.  Change PIN\n");
        printf("  5.  Logout\n\n");
        print_line('-', 48);
        printf("  Choose an option (1-5): ");

        choice = read_int();

        switch (choice) {
            case 1: show_balance(idx); break;
            case 2: deposit(idx);      break;
            case 3: withdraw(idx);     break;
            case 4: change_pin(idx);   break;
            case 5:
                print_header("THANK YOU");
                printf("\n  You have been logged out safely.\n");
                printf("  Please take your card.\n\n");
                print_line('=', 48);
                return;
            default:
                printf("\n  [!] Invalid choice. Please press 1, 2, 3, 4 or 5.\n");
                press_enter_to_continue();
        }
    }
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {
    while (1) {
        print_header("  ATM SIMULATION  ");
        printf("\n  1.  Insert Card (Login)\n");
        printf("  2.  Exit\n\n");
        print_line('-', 48);
        printf("  Your choice: ");

        int opt = read_int();

        if (opt == 1) {
            int idx = login();
            if (idx >= 0)
                account_menu(idx);
        } else if (opt == 2) {
            printf("\n  Thank you for using our ATM. Goodbye!\n\n");
            return 0;
        } else {
            printf("\n  [!] Please press 1 to login or 2 to exit.\n");
            press_enter_to_continue();
        }
    }
}