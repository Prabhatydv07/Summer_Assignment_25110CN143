#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define NAME_LEN 50
#define DEPT_LEN 50

/* ─── Data Structures ──────────────────────────────────────────────────── */

typedef struct {
    int    id;
    char   name[NAME_LEN];
    char   department[DEPT_LEN];
    float  salary;
    int    age;
} Employee;

/* ─── Global Store ─────────────────────────────────────────────────────── */

Employee employees[MAX_EMPLOYEES];
int      employee_count = 0;

/* ─── Utility ──────────────────────────────────────────────────────────── */

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_separator(void) {
    printf("─────────────────────────────────────────────────────────────\n");
}

void print_header(void) {
    printf("\n");
    print_separator();
    printf("          EMPLOYEE MANAGEMENT SYSTEM\n");
    print_separator();
}

int find_employee_by_id(int id) {
    for (int i = 0; i < employee_count; i++)
        if (employees[i].id == id)
            return i;
    return -1;
}

int id_exists(int id) {
    return find_employee_by_id(id) != -1;
}

void print_employee(const Employee *e) {
    printf("  ID         : %d\n",   e->id);
    printf("  Name       : %s\n",   e->name);
    printf("  Department : %s\n",   e->department);
    printf("  Salary     : ₹%.2f\n", e->salary);
    printf("  Age        : %d\n",   e->age);
}

void print_employee_row(const Employee *e) {
    printf("  %-6d %-20s %-18s %-12.2f %d\n",
           e->id, e->name, e->department, e->salary, e->age);
}

/* ─── Core Operations ──────────────────────────────────────────────────── */

void add_employee(void) {
    if (employee_count >= MAX_EMPLOYEES) {
        printf("\n  [!] Employee limit reached (%d).\n", MAX_EMPLOYEES);
        return;
    }

    Employee e;

    printf("\n  ── Add New Employee ──\n");

    printf("  Enter Employee ID   : ");
    if (scanf("%d", &e.id) != 1) { clear_input_buffer(); printf("  [!] Invalid ID.\n"); return; }
    clear_input_buffer();

    if (id_exists(e.id)) {
        printf("  [!] Employee with ID %d already exists.\n", e.id);
        return;
    }

    printf("  Enter Name          : ");
    fgets(e.name, NAME_LEN, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';

    printf("  Enter Department    : ");
    fgets(e.department, DEPT_LEN, stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("  Enter Salary        : ");
    if (scanf("%f", &e.salary) != 1 || e.salary < 0) {
        clear_input_buffer(); printf("  [!] Invalid salary.\n"); return;
    }
    clear_input_buffer();

    printf("  Enter Age           : ");
    if (scanf("%d", &e.age) != 1 || e.age < 18 || e.age > 100) {
        clear_input_buffer(); printf("  [!] Invalid age (must be 18–100).\n"); return;
    }
    clear_input_buffer();

    employees[employee_count++] = e;
    printf("\n  [✓] Employee '%s' added successfully.\n", e.name);
}

void display_all_employees(void) {
    printf("\n  ── All Employees ──\n");

    if (employee_count == 0) {
        printf("  No employees found.\n");
        return;
    }

    printf("\n  %-6s %-20s %-18s %-12s %s\n",
           "ID", "Name", "Department", "Salary", "Age");
    print_separator();

    for (int i = 0; i < employee_count; i++)
        print_employee_row(&employees[i]);

    printf("\n  Total Employees: %d\n", employee_count);
}

void search_employee(void) {
    int id;
    printf("\n  ── Search Employee ──\n");
    printf("  Enter Employee ID to search: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("  [!] Invalid input.\n"); return; }
    clear_input_buffer();

    int idx = find_employee_by_id(id);
    if (idx == -1) {
        printf("  [!] No employee found with ID %d.\n", id);
        return;
    }

    printf("\n  Employee Details:\n");
    print_separator();
    print_employee(&employees[idx]);
}

void update_employee(void) {
    int id;
    printf("\n  ── Update Employee ──\n");
    printf("  Enter Employee ID to update: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("  [!] Invalid input.\n"); return; }
    clear_input_buffer();

    int idx = find_employee_by_id(id);
    if (idx == -1) {
        printf("  [!] No employee found with ID %d.\n", id);
        return;
    }

    Employee *e = &employees[idx];
    printf("  Updating '%s' (leave blank to keep current value):\n\n", e->name);

    char buffer[NAME_LEN];

    printf("  New Name [%s]: ", e->name);
    fgets(buffer, NAME_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) strcpy(e->name, buffer);

    printf("  New Department [%s]: ", e->department);
    fgets(buffer, DEPT_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) strcpy(e->department, buffer);

    printf("  New Salary [%.2f]: ", e->salary);
    fgets(buffer, NAME_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        float s = atof(buffer);
        if (s >= 0) e->salary = s;
        else printf("  [!] Invalid salary; keeping current.\n");
    }

    printf("  New Age [%d]: ", e->age);
    fgets(buffer, NAME_LEN, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        int a = atoi(buffer);
        if (a >= 18 && a <= 100) e->age = a;
        else printf("  [!] Invalid age; keeping current.\n");
    }

    printf("\n  [✓] Employee updated successfully.\n");
}

void delete_employee(void) {
    int id;
    printf("\n  ── Delete Employee ──\n");
    printf("  Enter Employee ID to delete: ");
    if (scanf("%d", &id) != 1) { clear_input_buffer(); printf("  [!] Invalid input.\n"); return; }
    clear_input_buffer();

    int idx = find_employee_by_id(id);
    if (idx == -1) {
        printf("  [!] No employee found with ID %d.\n", id);
        return;
    }

    char confirm;
    printf("  Confirm delete '%s'? (y/n): ", employees[idx].name);
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm != 'y' && confirm != 'Y') {
        printf("  [–] Deletion cancelled.\n");
        return;
    }

    /* Shift left */
    for (int i = idx; i < employee_count - 1; i++)
        employees[i] = employees[i + 1];
    employee_count--;

    printf("  [✓] Employee deleted successfully.\n");
}

void department_report(void) {
    printf("\n  ── Department Report ──\n");
    if (employee_count == 0) { printf("  No employees found.\n"); return; }

    char dept[DEPT_LEN];
    printf("  Enter Department name: ");
    fgets(dept, DEPT_LEN, stdin);
    dept[strcspn(dept, "\n")] = '\0';

    int    count  = 0;
    double total  = 0.0;
    float  highest = -1.0f, lowest = -1.0f;

    printf("\n  %-6s %-20s %-12s %s\n", "ID", "Name", "Salary", "Age");
    print_separator();

    for (int i = 0; i < employee_count; i++) {
        if (strcasecmp(employees[i].department, dept) == 0) {
            print_employee_row(&employees[i]);
            total += employees[i].salary;
            count++;
            if (highest < 0 || employees[i].salary > highest) highest = employees[i].salary;
            if (lowest  < 0 || employees[i].salary < lowest)  lowest  = employees[i].salary;
        }
    }

    if (count == 0) {
        printf("  No employees in department '%s'.\n", dept);
        return;
    }

    print_separator();
    printf("  Count    : %d\n",    count);
    printf("  Total    : ₹%.2f\n", total);
    printf("  Average  : ₹%.2f\n", total / count);
    printf("  Highest  : ₹%.2f\n", highest);
    printf("  Lowest   : ₹%.2f\n", lowest);
}

void salary_report(void) {
    printf("\n  ── Salary Statistics ──\n");
    if (employee_count == 0) { printf("  No employees found.\n"); return; }

    double total   = 0.0;
    float  highest = employees[0].salary, lowest = employees[0].salary;
    int    hi_idx  = 0, lo_idx = 0;

    for (int i = 0; i < employee_count; i++) {
        total += employees[i].salary;
        if (employees[i].salary > highest) { highest = employees[i].salary; hi_idx = i; }
        if (employees[i].salary < lowest)  { lowest  = employees[i].salary; lo_idx = i; }
    }

    printf("\n  Total Employees : %d\n",      employee_count);
    printf("  Total Payroll   : ₹%.2f\n",    total);
    printf("  Average Salary  : ₹%.2f\n",    total / employee_count);
    printf("  Highest         : ₹%.2f  (%s, ID %d)\n", highest, employees[hi_idx].name, employees[hi_idx].id);
    printf("  Lowest          : ₹%.2f  (%s, ID %d)\n", lowest,  employees[lo_idx].name, employees[lo_idx].id);
}

void save_to_file(void) {
    FILE *fp = fopen("employees.dat", "wb");
    if (!fp) { printf("  [!] Could not open file for writing.\n"); return; }
    fwrite(&employee_count, sizeof(int), 1, fp);
    fwrite(employees, sizeof(Employee), employee_count, fp);
    fclose(fp);
    printf("  [✓] Data saved to 'employees.dat'.\n");
}

void load_from_file(void) {
    FILE *fp = fopen("employees.dat", "rb");
    if (!fp) { printf("  [–] No saved data found.\n"); return; }
    fread(&employee_count, sizeof(int), 1, fp);
    fread(employees, sizeof(Employee), employee_count, fp);
    fclose(fp);
    printf("  [✓] Loaded %d employee(s) from 'employees.dat'.\n", employee_count);
}

/* ─── Menu ─────────────────────────────────────────────────────────────── */

void show_menu(void) {
    print_header();
    printf("   1. Add Employee\n");
    printf("   2. Display All Employees\n");
    printf("   3. Search Employee\n");
    printf("   4. Update Employee\n");
    printf("   5. Delete Employee\n");
    printf("   6. Department Report\n");
    printf("   7. Salary Statistics\n");
    printf("   8. Save Data\n");
    printf("   9. Load Data\n");
    printf("   0. Exit\n");
    print_separator();
    printf("  Enter choice: ");
}

int main(void) {
    int choice;

    /* Auto-load on startup */
    load_from_file();

    while (1) {
        show_menu();

        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("  [!] Please enter a number.\n");
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1: add_employee();       break;
            case 2: display_all_employees(); break;
            case 3: search_employee();    break;
            case 4: update_employee();    break;
            case 5: delete_employee();    break;
            case 6: department_report();  break;
            case 7: salary_report();      break;
            case 8: save_to_file();       break;
            case 9: load_from_file();     break;
            case 0:
                save_to_file();
                printf("\n  Goodbye!\n\n");
                return 0;
            default:
                printf("  [!] Invalid choice. Please enter 0–9.\n");
        }
    }
}