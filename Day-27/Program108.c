#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS  100
#define MAX_SUBJECTS  6
#define NAME_LEN      50
#define PASS_MARK     35

// ─── Structures ───────────────────────────────────────────────────────────────

typedef struct {
    int   roll_no;
    char  name[NAME_LEN];
    char  class[NAME_LEN];
    int   marks[MAX_SUBJECTS];
    int   total;
    float percentage;
    float cgpa;       // out of 10
    char  grade[3];
    char  result[10]; // PASS / FAIL
} Student;

// ─── Subject Names ────────────────────────────────────────────────────────────

const char *subjects[MAX_SUBJECTS] = {
    "Mathematics",
    "Physics",
    "Chemistry",
    "English",
    "Computer Science",
    "Physical Education"
};
const int MAX_MARK = 100;

// ─── Global Data ─────────────────────────────────────────────────────────────

Student students[MAX_STUDENTS];
int student_count = 0;

// ─── Helpers ─────────────────────────────────────────────────────────────────

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
    printf("         MARKSHEET GENERATION SYSTEM\n");
    print_line('=', 65);
    printf("  >> %s\n", title);
    print_line('-', 65);
}

int find_student(int roll) {
    for (int i = 0; i < student_count; i++)
        if (students[i].roll_no == roll) return i;
    return -1;
}

// ─── Grade & Result Logic ────────────────────────────────────────────────────

void assign_grade(Student *s) {
    // Check for any subject failure
    int failed = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++)
        if (s->marks[i] < PASS_MARK) { failed = 1; break; }

    if (failed) {
        strcpy(s->result, "FAIL");
        strcpy(s->grade,  "F");
        s->cgpa = 0.0f;
        return;
    }

    strcpy(s->result, "PASS");

    if      (s->percentage >= 90) { strcpy(s->grade, "A+"); s->cgpa = 10.0f; }
    else if (s->percentage >= 80) { strcpy(s->grade, "A");  s->cgpa = 9.0f;  }
    else if (s->percentage >= 70) { strcpy(s->grade, "B+"); s->cgpa = 8.0f;  }
    else if (s->percentage >= 60) { strcpy(s->grade, "B");  s->cgpa = 7.0f;  }
    else if (s->percentage >= 50) { strcpy(s->grade, "C+"); s->cgpa = 6.0f;  }
    else if (s->percentage >= 40) { strcpy(s->grade, "C");  s->cgpa = 5.0f;  }
    else                          { strcpy(s->grade, "D");  s->cgpa = 4.0f;  }
}

void calculate_result(Student *s) {
    s->total = 0;
    for (int i = 0; i < MAX_SUBJECTS; i++)
        s->total += s->marks[i];
    s->percentage = (float)s->total / (MAX_SUBJECTS * MAX_MARK) * 100.0f;
    assign_grade(s);
}

// ─── Print Marksheet ─────────────────────────────────────────────────────────

void print_marksheet(const Student *s) {
    print_line('*', 65);
    printf("*%63s*\n", " ");
    printf("*       OFFICIAL MARK SHEET / REPORT CARD%22s*\n", " ");
    printf("*%63s*\n", " ");
    print_line('*', 65);

    printf("  Roll No     : %-10d   Class : %s\n", s->roll_no, s->class);
    printf("  Student Name: %s\n", s->name);
    print_line('-', 65);

    printf("  %-4s  %-22s  %8s  %8s  %6s\n",
           "No.", "Subject", "Max Marks", "Obtained", "Status");
    print_line('-', 65);

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        const char *status = (s->marks[i] >= PASS_MARK) ? "PASS" : "FAIL";
        printf("  %-4d  %-22s  %8d  %8d  %6s\n",
               i + 1, subjects[i], MAX_MARK, s->marks[i], status);
    }

    print_line('-', 65);
    printf("  %-26s  %8d  %8d\n",
           "TOTAL", MAX_SUBJECTS * MAX_MARK, s->total);
    print_line('=', 65);
    printf("  Percentage : %.2f%%\n",  s->percentage);
    printf("  CGPA       : %.1f / 10\n", s->cgpa);
    printf("  Grade      : %s\n",       s->grade);
    printf("  Result     : %s\n",       s->result);
    print_line('*', 65);
}

// ─── Operations ──────────────────────────────────────────────────────────────

void add_student() {
    print_header("ADD STUDENT");

    if (student_count >= MAX_STUDENTS) {
        printf("  ERROR: Maximum student limit reached.\n");
        pause_screen(); return;
    }

    Student s;
    printf("  Enter Roll Number : "); scanf("%d", &s.roll_no);

    if (find_student(s.roll_no) != -1) {
        printf("  ERROR: Roll number %d already exists.\n", s.roll_no);
        pause_screen(); return;
    }

    printf("  Enter Student Name: "); scanf(" %[^\n]", s.name);
    printf("  Enter Class/Course: "); scanf(" %[^\n]", s.class);

    printf("\n  Enter marks out of %d for each subject:\n\n", MAX_MARK);
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("  [%d] %-22s : ", i + 1, subjects[i]);
        scanf("%d", &s.marks[i]);

        if (s.marks[i] < 0 || s.marks[i] > MAX_MARK) {
            printf("      Invalid! Marks must be 0-%d. Re-enter: ", MAX_MARK);
            scanf("%d", &s.marks[i]);
        }
    }

    calculate_result(&s);
    students[student_count++] = s;

    printf("\n  ✔ Student record added successfully!\n");
    printf("  Result : %s | Percentage : %.2f%% | Grade : %s\n",
           s.result, s.percentage, s.grade);
    pause_screen();
}

void view_marksheet() {
    print_header("VIEW MARK SHEET");

    int roll;
    printf("  Enter Roll Number: "); scanf("%d", &roll);

    int idx = find_student(roll);
    if (idx == -1) {
        printf("  ERROR: Student with Roll No. %d not found.\n", roll);
        pause_screen(); return;
    }

    printf("\n");
    print_marksheet(&students[idx]);
    pause_screen();
}

void view_all_students() {
    print_header("ALL STUDENTS SUMMARY");

    if (student_count == 0) {
        printf("  No student records found.\n");
        pause_screen(); return;
    }

    printf("  %-6s  %-22s  %-12s  %6s  %7s  %5s  %6s\n",
           "Roll", "Name", "Class", "Total", "Percent", "Grade", "Result");
    print_line('-', 72);

    for (int i = 0; i < student_count; i++) {
        Student *s = &students[i];
        printf("  %-6d  %-22s  %-12s  %6d  %6.2f%%  %5s  %6s\n",
               s->roll_no, s->name, s->class,
               s->total, s->percentage, s->grade, s->result);
    }

    print_line('-', 72);
    printf("  Total Students: %d\n", student_count);
    pause_screen();
}

void update_marks() {
    print_header("UPDATE MARKS");

    int roll;
    printf("  Enter Roll Number: "); scanf("%d", &roll);

    int idx = find_student(roll);
    if (idx == -1) {
        printf("  ERROR: Student with Roll No. %d not found.\n", roll);
        pause_screen(); return;
    }

    Student *s = &students[idx];
    printf("  Student: %s | Class: %s\n\n", s->name, s->class);

    printf("  Which subject to update?\n");
    for (int i = 0; i < MAX_SUBJECTS; i++)
        printf("  [%d] %-22s  (Current: %d)\n", i + 1, subjects[i], s->marks[i]);

    int choice;
    printf("\n  Enter subject number (1-%d): ", MAX_SUBJECTS);
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_SUBJECTS) {
        printf("  ERROR: Invalid subject number.\n");
        pause_screen(); return;
    }

    printf("  Enter new marks for %s: ", subjects[choice - 1]);
    scanf("%d", &s->marks[choice - 1]);

    calculate_result(s);
    printf("\n  ✔ Marks updated! New Result: %s | %.2f%% | Grade: %s\n",
           s->result, s->percentage, s->grade);
    pause_screen();
}

void delete_student() {
    print_header("DELETE STUDENT");

    int roll;
    printf("  Enter Roll Number to delete: "); scanf("%d", &roll);

    int idx = find_student(roll);
    if (idx == -1) {
        printf("  ERROR: Student with Roll No. %d not found.\n", roll);
        pause_screen(); return;
    }

    printf("  Deleting: %s (Roll: %d)\n", students[idx].name, students[idx].roll_no);
    printf("  Are you sure? (y/n): ");
    char c; scanf(" %c", &c);

    if (c == 'y' || c == 'Y') {
        for (int i = idx; i < student_count - 1; i++)
            students[i] = students[i + 1];
        student_count--;
        printf("\n  ✔ Student record deleted.\n");
    } else {
        printf("\n  Deletion cancelled.\n");
    }
    pause_screen();
}

void search_student() {
    print_header("SEARCH STUDENT");

    printf("  Search by:\n");
    printf("  [1] Roll Number\n");
    printf("  [2] Name\n");
    printf("  Enter choice: ");
    int ch; scanf("%d", &ch);

    if (ch == 1) {
        int roll;
        printf("  Enter Roll Number: "); scanf("%d", &roll);
        int idx = find_student(roll);
        if (idx == -1) { printf("  Not found.\n"); pause_screen(); return; }
        printf("\n"); print_marksheet(&students[idx]);

    } else if (ch == 2) {
        char name[NAME_LEN];
        printf("  Enter Name (or partial): "); scanf(" %[^\n]", name);
        int found = 0;
        for (int i = 0; i < student_count; i++) {
            if (strstr(students[i].name, name) != NULL) {
                printf("\n"); print_marksheet(&students[i]);
                found = 1;
            }
        }
        if (!found) printf("  No student found with name containing '%s'.\n", name);
    } else {
        printf("  Invalid choice.\n");
    }
    pause_screen();
}

// ─── Class Topper ─────────────────────────────────────────────────────────────

void class_topper() {
    print_header("CLASS TOPPER");

    if (student_count == 0) {
        printf("  No student records found.\n");
        pause_screen(); return;
    }

    int top = 0;
    for (int i = 1; i < student_count; i++)
        if (students[i].percentage > students[top].percentage)
            top = i;

    Student *s = &students[top];
    printf("\n  🏆 CLASS TOPPER\n\n");
    printf("  Roll No    : %d\n",     s->roll_no);
    printf("  Name       : %s\n",     s->name);
    printf("  Class      : %s\n",     s->class);
    printf("  Total      : %d / %d\n", s->total, MAX_SUBJECTS * MAX_MARK);
    printf("  Percentage : %.2f%%\n", s->percentage);
    printf("  CGPA       : %.1f / 10\n", s->cgpa);
    printf("  Grade      : %s\n",     s->grade);
    pause_screen();
}

// ─── Statistics ───────────────────────────────────────────────────────────────

void class_statistics() {
    print_header("CLASS STATISTICS");

    if (student_count == 0) {
        printf("  No records found.\n");
        pause_screen(); return;
    }

    int pass = 0, fail = 0;
    float sum = 0, highest = 0, lowest = 100;

    int grade_count[7] = {0}; // A+, A, B+, B, C+, C, D/F
    const char *grade_labels[] = {"A+", "A", "B+", "B", "C+", "C", "D/F"};

    for (int i = 0; i < student_count; i++) {
        Student *s = &students[i];
        if (strcmp(s->result, "PASS") == 0) pass++; else fail++;
        sum += s->percentage;
        if (s->percentage > highest) highest = s->percentage;
        if (s->percentage < lowest)  lowest  = s->percentage;

        if      (strcmp(s->grade, "A+") == 0) grade_count[0]++;
        else if (strcmp(s->grade, "A")  == 0) grade_count[1]++;
        else if (strcmp(s->grade, "B+") == 0) grade_count[2]++;
        else if (strcmp(s->grade, "B")  == 0) grade_count[3]++;
        else if (strcmp(s->grade, "C+") == 0) grade_count[4]++;
        else if (strcmp(s->grade, "C")  == 0) grade_count[5]++;
        else                                   grade_count[6]++;
    }

    printf("  Total Students    : %d\n",    student_count);
    printf("  Passed            : %d\n",    pass);
    printf("  Failed            : %d\n",    fail);
    printf("  Pass Percentage   : %.2f%%\n",(float)pass / student_count * 100);
    print_line('-', 65);
    printf("  Highest Score     : %.2f%%\n", highest);
    printf("  Lowest Score      : %.2f%%\n", lowest);
    printf("  Class Average     : %.2f%%\n", sum / student_count);
    print_line('-', 65);
    printf("  Grade Distribution:\n\n");
    for (int i = 0; i < 7; i++) {
        printf("    %-4s : %d student(s)\n", grade_labels[i], grade_count[i]);
    }
    pause_screen();
}

// ─── Subject-wise Analysis ───────────────────────────────────────────────────

void subject_analysis() {
    print_header("SUBJECT-WISE ANALYSIS");

    if (student_count == 0) {
        printf("  No records found.\n");
        pause_screen(); return;
    }

    printf("  %-22s  %8s  %8s  %8s  %6s\n",
           "Subject", "Highest", "Lowest", "Average", "Pass%");
    print_line('-', 60);

    for (int s = 0; s < MAX_SUBJECTS; s++) {
        int high = 0, low = MAX_MARK, total = 0, pass = 0;
        for (int i = 0; i < student_count; i++) {
            int m = students[i].marks[s];
            if (m > high) high = m;
            if (m < low)  low  = m;
            total += m;
            if (m >= PASS_MARK) pass++;
        }
        printf("  %-22s  %8d  %8d  %8.2f  %5.1f%%\n",
               subjects[s], high, low,
               (float)total / student_count,
               (float)pass / student_count * 100);
    }
    print_line('-', 60);
    pause_screen();
}

// ─── Rank List ────────────────────────────────────────────────────────────────

void rank_list() {
    print_header("RANK LIST");

    if (student_count == 0) {
        printf("  No records found.\n");
        pause_screen(); return;
    }

    // Copy and sort by percentage descending (bubble sort)
    Student sorted[MAX_STUDENTS];
    memcpy(sorted, students, student_count * sizeof(Student));

    for (int i = 0; i < student_count - 1; i++)
        for (int j = 0; j < student_count - i - 1; j++)
            if (sorted[j].percentage < sorted[j + 1].percentage) {
                Student tmp = sorted[j];
                sorted[j]   = sorted[j + 1];
                sorted[j + 1] = tmp;
            }

    printf("  %-5s  %-6s  %-22s  %-12s  %7s  %5s\n",
           "Rank", "Roll", "Name", "Class", "Percent", "Grade");
    print_line('-', 65);

    for (int i = 0; i < student_count; i++) {
        printf("  %-5d  %-6d  %-22s  %-12s  %6.2f%%  %5s\n",
               i + 1, sorted[i].roll_no, sorted[i].name,
               sorted[i].class, sorted[i].percentage, sorted[i].grade);
    }
    print_line('-', 65);
    pause_screen();
}

// ─── Main Menu ────────────────────────────────────────────────────────────────

void show_menu() {
    print_header("MAIN MENU");
    printf("  [1]  Add Student & Enter Marks\n");
    printf("  [2]  View Mark Sheet\n");
    printf("  [3]  View All Students (Summary)\n");
    printf("  [4]  Search Student\n");
    printf("  [5]  Update Marks\n");
    printf("  [6]  Delete Student\n");
    printf("  [7]  Class Topper\n");
    printf("  [8]  Rank List\n");
    printf("  [9]  Class Statistics\n");
    printf("  [10] Subject-wise Analysis\n");
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
            case  1: add_student();       break;
            case  2: view_marksheet();    break;
            case  3: view_all_students(); break;
            case  4: search_student();    break;
            case  5: update_marks();      break;
            case  6: delete_student();    break;
            case  7: class_topper();      break;
            case  8: rank_list();         break;
            case  9: class_statistics();  break;
            case 10: subject_analysis();  break;
            case  0:
                clear_screen();
                printf("  Thank you for using Marksheet Generation System. Goodbye!\n\n");
                return 0;
            default:
                printf("  Invalid choice. Please enter 0-10.\n");
                pause_screen();
        }
    }
}