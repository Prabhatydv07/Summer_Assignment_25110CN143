#include <stdio.h>

struct Ticket {
    char name[50];
    int age;
    int ticketNo;
    int seats;
};

int main() {
    struct Ticket t;

    printf("Enter Passenger Name: ");
    scanf("%s", t.name);

    printf("Enter Age: ");
    scanf("%d", &t.age);

    printf("Enter Ticket Number: ");
    scanf("%d", &t.ticketNo);

    printf("Enter Number of Seats: ");
    scanf("%d", &t.seats);

    printf("\n----- Ticket Details -----\n");
    printf("Passenger Name : %s\n", t.name);
    printf("Age            : %d\n", t.age);
    printf("Ticket Number  : %d\n", t.ticketNo);
    printf("Seats Booked   : %d\n", t.seats);

    return 0;
}