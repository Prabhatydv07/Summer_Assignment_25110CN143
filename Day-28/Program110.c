#include <stdio.h>

struct BankAccount {
    int accountNumber;
    char name[50];
    float balance;
};

int main() {
    struct BankAccount account;

    printf("Enter Account Number: ");
    scanf("%d", &account.accountNumber);

    printf("Enter Account Holder Name: ");
    scanf("%s", account.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &account.balance);

    printf("\n--- Bank Account Details ---\n");
    printf("Account Number : %d\n", account.accountNumber);
    printf("Account Holder : %s\n", account.name);
    printf("Balance        : %.2f\n", account.balance);

    return 0;
}