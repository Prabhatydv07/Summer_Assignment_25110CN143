#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define NAME_LEN 50

// ─── Structures ───────────────────────────────────────────────────────────────

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   department[NAME_LEN];
    char   designation[NAME_LEN];
    float  basic_salary;
    float  hra;          // House Rent Allowance  (40% of basic)
    float  da;           // Dearness Allowance    (20% of basic)
    float  ta;           // Travel Allowance      (10% of basic)
    float  pf;           // Provident Fund        (12% of basic, deduction)
    float  tax;          // Income Tax            (10% of basic, deduction)
    float  gross_salary;
    float  net_salary;
} Employee;

// ─── Global Data ─────────────────────────────────────────────────────────────

Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

// ─── Helper Functions ─────────────────────────────────────────────────────────

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_screen() {
    printf("\n  Press Enter to continue...");
    getchar();
    getchar();
}

void print_line(char c, int n) {
    for (int i = 0; i < n; i++) putchar(c);
    putchar('\n');
}

void print_header(const char *title) {
    clear_screen();
    print_line('=', 65);
    printf("          SALARY MANAGEMENT SYSTEM\n");
    print_line('=', 65);
    printf("  >> %s\n", title);
    print_line('-', 65);
}

// ─── Salary Calculations ─────────────────────────────────────────────────────

void calculate_salary(Employee *e) {
    e->hra         = 0.40f * e->basic_salary;
    e->da          = 0.20f * e->basic_salary;
    e->ta          = 0.10f * e->basic_salary;
    e->pf          = 0.12f * e->basic_salary;
    e->tax         = 0.10f * e->basic_salary;
    e->gross_salary = e->basic_salary + e->hra + e->da + e->ta;
    e->net_salary   = e->gross_salary - e->pf - e->tax;
}

// ─── Find employee by ID (returns index or -1) ────────────────────────────────

int find_employee(int id) {
    for (int i = 0; i < employee_count; i++)
        if (employees[i].id == id) return i;
    return -1;
}

// ─── Print Payslip ────────────────────────────────────────────────────────────

void print_payslip(const Employee *e) {
    print_line('=', 65);
    printf("                     PAY SLIP\n");
    print_line('=', 65);
    printf("  Employee ID   : %d\n",    e->id);
    printf("  Name          : %s\n",    e->name);
    printf("  Department    : %s\n",    e->department);
    printf("  Designation   : %s\n",    e->designation);
    print_line('-', 65);
    printf("  %-30s %10s %10s\n", "COMPONENT", "EARNINGS", "DEDUCTIONS");
    print_line('-', 65);
    printf("  %-30s %10.2f\n",    "Basic Salary",          e->basic_salary);
    printf("  %-30s %10.2f\n",    "HRA (40% of Basic)",    e->hra);
    printf("  %-30s %10.2f\n",    "DA  (20% of Basic)",    e->da);
    printf("  %-30s %10.2f\n",    "TA  (10% of Basic)",    e->ta);
    printf("  %-30s %20.2f\n",    "PF  (12% of Basic)",    e->pf);
    printf("  %-30s %20.2f\n",    "Income Tax (10%)",      e->tax);
    print_line('-', 65);
    printf("  %-30s %10.2f %10.2f\n",
           "TOTAL", e->gross_salary, e->pf + e->tax);
    print_line('=', 65);
    printf("  NET SALARY PAYABLE        : Rs. %.2f\n", e->net_salary);
    print_line('=', 65);
}

// ─── Menu Operations ─────────────────────────────────────────────────────────

void add_employee() {
    print_header("ADD EMPLOYEE");

    if (employee_count >= MAX_EMPLOYEES) {
        printf("  ERROR: Maximum employee limit (%d) reached.\n", MAX_EMPLOYEES);
        pause_screen(); return;
    }

    Employee e;
    printf("  Enter Employee ID     : "); scanf("%d",  &e.id);

    if (find_employee(e.id) != -1) {
        printf("  ERROR: Employee with ID %d already exists.\n", e.id);
        pause_screen(); return;
    }

    printf("  Enter Name            : "); scanf(" %[^\n]", e.name);
    printf("  Enter Department      : "); scanf(" %[^\n]", e.department);
    printf("  Enter Designation     : "); scanf(" %[^\n]", e.designation);
    printf("  Enter Basic Salary    : Rs. "); scanf("%f", &e.basic_salary);

    if (e.basic_salary < 0) {
        printf("  ERROR: Salary cannot be negative.\n");
        pause_screen(); return;
    }

    calculate_salary(&e);
    employees[employee_count++] = e;

    printf("\n  ✔ Employee added successfully!\n");
    pause_screen();
}

void view_all_employees() {
    print_header("ALL EMPLOYEES");

    if (employee_count == 0) {
        printf("  No employees found.\n");
        pause_screen(); return;
    }

    printf("  %-5s %-20s %-15s %-15s %12s %12s\n",
           "ID", "Name", "Department", "Designation", "Basic(Rs.)", "Net(Rs.)");
    print_line('-', 85);

    for (int i = 0; i < employee_count; i++) {
        Employee *e = &employees[i];
        printf("  %-5d %-20s %-15s %-15s %12.2f %12.2f\n",
               e->id, e->name, e->department,
               e->designation, e->basic_salary, e->net_salary);
    }
    print_line('-', 85);
    printf("  Total Employees: %d\n", employee_count);
    pause_screen();
}

void view_payslip() {
    print_header("VIEW PAY SLIP");

    int id;
    printf("  Enter Employee ID: "); scanf("%d", &id);

    int idx = find_employee(id);
    if (idx == -1) {
        printf("  ERROR: Employee with ID %d not found.\n", id);
        pause_screen(); return;
    }

    print_payslip(&employees[idx]);
    pause_screen();
}

void update_salary() {
    print_header("UPDATE SALARY");

    int id;
    printf("  Enter Employee ID: "); scanf("%d", &id);

    int idx = find_employee(id);
    if (idx == -1) {
        printf("  ERROR: Employee with ID %d not found.\n", id);
        pause_screen(); return;
    }

    Employee *e = &employees[idx];
    printf("  Employee  : %s\n", e->name);
    printf("  Current Basic Salary : Rs. %.2f\n", e->basic_salary);
    printf("  Enter New Basic Salary: Rs. "); scanf("%f", &e->basic_salary);

    if (e->basic_salary < 0) {
        printf("  ERROR: Salary cannot be negative.\n");
        pause_screen(); return;
    }

    calculate_salary(e);
    printf("\n  ✔ Salary updated successfully! New Net Salary: Rs. %.2f\n", e->net_salary);
    pause_screen();
}

void delete_employee() {
    print_header("DELETE EMPLOYEE");

    int id;
    printf("  Enter Employee ID to delete: "); scanf("%d", &id);

    int idx = find_employee(id);
    if (idx == -1) {
        printf("  ERROR: Employee with ID %d not found.\n", id);
        pause_screen(); return;
    }

    printf("  Deleting: %s (%s)\n", employees[idx].name, employees[idx].department);
    printf("  Are you sure? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        // Shift remaining employees left
        for (int i = idx; i < employee_count - 1; i++)
            employees[i] = employees[i + 1];
        employee_count--;
        printf("\n  ✔ Employee deleted successfully.\n");
    } else {
        printf("\n  Deletion cancelled.\n");
    }
    pause_screen();
}

void search_employee() {
    print_header("SEARCH EMPLOYEE");

    int id;
    printf("  Enter Employee ID: "); scanf("%d", &id);

    int idx = find_employee(id);
    if (idx == -1) {
        printf("  ERROR: Employee with ID %d not found.\n", id);
        pause_screen(); return;
    }

    Employee *e = &employees[idx];
    printf("\n");
    printf("  Employee ID   : %d\n",    e->id);
    printf("  Name          : %s\n",    e->name);
    printf("  Department    : %s\n",    e->department);
    printf("  Designation   : %s\n",    e->designation);
    printf("  Basic Salary  : Rs. %.2f\n", e->basic_salary);
    printf("  Gross Salary  : Rs. %.2f\n", e->gross_salary);
    printf("  Net Salary    : Rs. %.2f\n", e->net_salary);
    pause_screen();
}

void department_summary() {
    print_header("DEPARTMENT SALARY SUMMARY");

    if (employee_count == 0) {
        printf("  No employees found.\n");
        pause_screen(); return;
    }

    // Collect unique departments
    char depts[MAX_EMPLOYEES][NAME_LEN];
    int  dept_count = 0;

    for (int i = 0; i < employee_count; i++) {
        int found = 0;
        for (int d = 0; d < dept_count; d++)
            if (strcmp(depts[d], employees[i].department) == 0) { found = 1; break; }
        if (!found) strcpy(depts[dept_count++], employees[i].department);
    }

    printf("  %-20s %8s %12s %12s %12s\n",
           "Department", "Count", "Total Basic", "Total Gross", "Total Net");
    print_line('-', 70);

    for (int d = 0; d < dept_count; d++) {
        int   cnt = 0;
        float total_basic = 0, total_gross = 0, total_net = 0;

        for (int i = 0; i < employee_count; i++) {
            if (strcmp(employees[i].department, depts[d]) == 0) {
                cnt++;
                total_basic += employees[i].basic_salary;
                total_gross += employees[i].gross_salary;
                total_net   += employees[i].net_salary;
            }
        }
        printf("  %-20s %8d %12.2f %12.2f %12.2f\n",
               depts[d], cnt, total_basic, total_gross, total_net);
    }
    print_line('-', 70);
    pause_screen();
}

// ─── Main Menu ────────────────────────────────────────────────────────────────

void show_menu() {
    print_header("MAIN MENU");
    printf("  [1]  Add Employee\n");
    printf("  [2]  View All Employees\n");
    printf("  [3]  Search Employee\n");
    printf("  [4]  View Pay Slip\n");
    printf("  [5]  Update Salary\n");
    printf("  [6]  Delete Employee\n");
    printf("  [7]  Department Salary Summary\n");
    printf("  [0]  Exit\n");
    print_line('-', 65);
    printf("  Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        show_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee();        break;
            case 2: view_all_employees();  break;
            case 3: search_employee();     break;
            case 4: view_payslip();        break;
            case 5: update_salary();       break;
            case 6: delete_employee();     break;
            case 7: department_summary();  break;
            case 0:
                clear_screen();
                printf("  Thank you for using Salary Management System. Goodbye!\n\n");
                return 0;
            default:
                printf("  Invalid choice. Please enter 0-7.\n");
                pause_screen();
        }
    }
}