/*
 * ================================================================
 *        STUDENT RECORD MANAGEMENT SYSTEM  (C Language)
 * ================================================================
 *  Features:
 *    1. Add    a new student record
 *    2. Display all student records
 *    3. Search a record by Roll Number
 *    4. Update  an existing record
 *    5. Delete  a record
 *    6. Display class result (sorted by marks, with grade/rank)
 *    7. Save records to file  (students.dat)
 *    8. Load records from file
 *    0. Exit
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ── Constants ─────────────────────────────────────────── */
#define MAX_STUDENTS  100
#define NAME_LEN       60
#define COURSE_LEN     40
#define DATA_FILE      "students.dat"

/* ── Colour macros (ANSI) ──────────────────────────────── */
#define CLR_RESET  "\033[0m"
#define CLR_BOLD   "\033[1m"
#define CLR_CYAN   "\033[1;36m"
#define CLR_GREEN  "\033[1;32m"
#define CLR_RED    "\033[1;31m"
#define CLR_YELLOW "\033[1;33m"
#define CLR_BLUE   "\033[1;34m"

/* ── Data structure ────────────────────────────────────── */
typedef struct {
    int   roll;
    char  name[NAME_LEN];
    char  course[COURSE_LEN];
    int   age;
    float marks[5];          /* marks for 5 subjects          */
    float total;             /* computed field                 */
    float percentage;        /* computed field                 */
    char  grade;             /* computed field                 */
} Student;

/* ── Global state ──────────────────────────────────────── */
Student db[MAX_STUDENTS];
int     count = 0;

/* ══════════════════════════════════════════════════════════
 *  UTILITY FUNCTIONS
 * ══════════════════════════════════════════════════════════ */

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause_screen(void) {
    printf("\n  Press ENTER to continue...");
    while (getchar() != '\n');
    getchar();
}

void flush_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void separator(const char *title) {
    printf(CLR_CYAN);
    printf("\n  ╔══════════════════════════════════════════════════════╗\n");
    if (title && title[0]) {
        int pad = (int)(54 - strlen(title)) / 2;
        printf("  ║%*s%s%*s║\n", pad, "", title,
               (int)(54 - pad - strlen(title)), "");
    }
    printf("  ╚══════════════════════════════════════════════════════╝\n");
    printf(CLR_RESET);
}

/* Compute total, percentage, grade for one student */
void compute_stats(Student *s) {
    s->total = 0;
    for (int i = 0; i < 5; i++) s->total += s->marks[i];
    s->percentage = s->total / 5.0f;

    if      (s->percentage >= 90) s->grade = 'O';  /* Outstanding  */
    else if (s->percentage >= 80) s->grade = 'A';
    else if (s->percentage >= 70) s->grade = 'B';
    else if (s->percentage >= 60) s->grade = 'C';
    else if (s->percentage >= 50) s->grade = 'D';
    else                          s->grade = 'F';  /* Fail         */
}

/* Find index of student with given roll number; -1 if not found */
int find_by_roll(int roll) {
    for (int i = 0; i < count; i++)
        if (db[i].roll == roll) return i;
    return -1;
}

/* Check if roll number already exists */
int roll_exists(int roll) {
    return find_by_roll(roll) != -1;
}

/* Print one student row in tabular form */
void print_row(int rank, Student *s) {
    if (rank > 0)
        printf("  %-5d", rank);
    else
        printf("  %-5s", " ");

    printf("%-8d %-20s %-18s %-5d",
           s->roll, s->name, s->course, s->age);
    printf("%7.1f  %6.2f%%   %c\n",
           s->total, s->percentage, s->grade);
}

/* Print table header */
void print_header(int show_rank) {
    printf(CLR_BOLD CLR_BLUE);
    if (show_rank)
        printf("  %-5s", "Rank");
    else
        printf("  %-5s", " ");
    printf("%-8s %-20s %-18s %-5s %7s  %7s  %s\n",
           "Roll", "Name", "Course", "Age", "Total", "Pct", "Grade");
    printf("  %s\n",
           "----------------------------------------------------------------------");
    printf(CLR_RESET);
}

/* ══════════════════════════════════════════════════════════
 *  1. ADD STUDENT
 * ══════════════════════════════════════════════════════════ */
void add_student(void) {
    separator("ADD NEW STUDENT");

    if (count >= MAX_STUDENTS) {
        printf(CLR_RED "  [!] Database full (%d students).\n" CLR_RESET,
               MAX_STUDENTS);
        pause_screen();
        return;
    }

    Student s;

    /* Roll number */
    while (1) {
        printf("  Roll Number : ");
        if (scanf("%d", &s.roll) != 1 || s.roll <= 0) {
            printf(CLR_RED "  [!] Invalid roll number.\n" CLR_RESET);
            flush_stdin(); continue;
        }
        flush_stdin();
        if (roll_exists(s.roll)) {
            printf(CLR_RED "  [!] Roll %d already exists.\n" CLR_RESET, s.roll);
            continue;
        }
        break;
    }

    /* Name */
    printf("  Full Name   : ");
    fgets(s.name, NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';
    if (strlen(s.name) == 0) { strcpy(s.name, "Unknown"); }

    /* Course */
    printf("  Course      : ");
    fgets(s.course, COURSE_LEN, stdin);
    s.course[strcspn(s.course, "\n")] = '\0';
    if (strlen(s.course) == 0) { strcpy(s.course, "General"); }

    /* Age */
    while (1) {
        printf("  Age         : ");
        if (scanf("%d", &s.age) == 1 && s.age > 0 && s.age < 120) break;
        printf(CLR_RED "  [!] Invalid age.\n" CLR_RESET);
        flush_stdin();
    }
    flush_stdin();

    /* Marks for 5 subjects */
    const char *subjects[] = {"Maths", "Science", "English", "History", "CS"};
    printf("  Enter marks (0-100) for each subject:\n");
    for (int i = 0; i < 5; i++) {
        while (1) {
            printf("    %-10s: ", subjects[i]);
            if (scanf("%f", &s.marks[i]) == 1 &&
                s.marks[i] >= 0 && s.marks[i] <= 100) break;
            printf(CLR_RED "  [!] Enter a value between 0 and 100.\n" CLR_RESET);
            flush_stdin();
        }
        flush_stdin();
    }

    compute_stats(&s);
    db[count++] = s;

    printf(CLR_GREEN "\n  ✔  Student added successfully! "
           "(Total: %.1f | %.2f%% | Grade: %c)\n" CLR_RESET,
           s.total, s.percentage, s.grade);
    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  2. DISPLAY ALL RECORDS
 * ══════════════════════════════════════════════════════════ */
void display_all(void) {
    separator("ALL STUDENT RECORDS");

    if (count == 0) {
        printf(CLR_YELLOW "  No records found.\n" CLR_RESET);
        pause_screen();
        return;
    }

    printf("  Total students: %d\n\n", count);
    print_header(0);
    for (int i = 0; i < count; i++)
        print_row(0, &db[i]);

    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  3. SEARCH BY ROLL NUMBER
 * ══════════════════════════════════════════════════════════ */
void search_student(void) {
    separator("SEARCH STUDENT");

    int roll;
    printf("  Enter Roll Number to search: ");
    scanf("%d", &roll);
    flush_stdin();

    int idx = find_by_roll(roll);
    if (idx == -1) {
        printf(CLR_RED "  [!] Student with roll %d not found.\n" CLR_RESET, roll);
        pause_screen();
        return;
    }

    Student *s = &db[idx];
    printf(CLR_GREEN "\n  ── Student Details ──────────────────────────────\n"
           CLR_RESET);
    printf("  Roll Number  : %d\n",   s->roll);
    printf("  Name         : %s\n",   s->name);
    printf("  Course       : %s\n",   s->course);
    printf("  Age          : %d\n",   s->age);

    const char *subjects[] = {"Maths", "Science", "English", "History", "CS"};
    printf("  Marks        :\n");
    for (int i = 0; i < 5; i++)
        printf("    %-10s: %.1f\n", subjects[i], s->marks[i]);

    printf("  Total        : %.1f / 500\n",   s->total);
    printf("  Percentage   : %.2f%%\n",         s->percentage);
    printf("  Grade        : %c\n",             s->grade);
    printf("  ─────────────────────────────────────────────────\n");

    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  4. UPDATE RECORD
 * ══════════════════════════════════════════════════════════ */
void update_student(void) {
    separator("UPDATE STUDENT RECORD");

    int roll;
    printf("  Enter Roll Number to update: ");
    scanf("%d", &roll);
    flush_stdin();

    int idx = find_by_roll(roll);
    if (idx == -1) {
        printf(CLR_RED "  [!] Roll %d not found.\n" CLR_RESET, roll);
        pause_screen();
        return;
    }

    Student *s = &db[idx];
    printf("  Updating record for: %s (Roll: %d)\n\n", s->name, s->roll);
    printf("  Leave blank/0 to keep current value.\n\n");

    /* Name */
    char buf[NAME_LEN];
    printf("  New Name [%s]: ", s->name);
    fgets(buf, NAME_LEN, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(s->name, buf);

    /* Course */
    printf("  New Course [%s]: ", s->course);
    fgets(buf, COURSE_LEN, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf) > 0) strcpy(s->course, buf);

    /* Age */
    int age;
    printf("  New Age [%d] (0 to keep): ", s->age);
    scanf("%d", &age);
    flush_stdin();
    if (age > 0 && age < 120) s->age = age;

    /* Marks */
    const char *subjects[] = {"Maths", "Science", "English", "History", "CS"};
    printf("  Update marks? (y/n): ");
    char ch;
    scanf(" %c", &ch);
    flush_stdin();
    if (ch == 'y' || ch == 'Y') {
        for (int i = 0; i < 5; i++) {
            float m;
            printf("    %-10s [%.1f]: ", subjects[i], s->marks[i]);
            if (scanf("%f", &m) == 1 && m >= 0 && m <= 100)
                s->marks[i] = m;
            flush_stdin();
        }
    }

    compute_stats(s);
    printf(CLR_GREEN "\n  ✔  Record updated. "
           "(Total: %.1f | %.2f%% | Grade: %c)\n" CLR_RESET,
           s->total, s->percentage, s->grade);
    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  5. DELETE RECORD
 * ══════════════════════════════════════════════════════════ */
void delete_student(void) {
    separator("DELETE STUDENT RECORD");

    int roll;
    printf("  Enter Roll Number to delete: ");
    scanf("%d", &roll);
    flush_stdin();

    int idx = find_by_roll(roll);
    if (idx == -1) {
        printf(CLR_RED "  [!] Roll %d not found.\n" CLR_RESET, roll);
        pause_screen();
        return;
    }

    printf("  Are you sure you want to delete " CLR_RED "%s" CLR_RESET
           " (Roll %d)? (y/n): ",
           db[idx].name, roll);
    char ch;
    scanf(" %c", &ch);
    flush_stdin();

    if (ch != 'y' && ch != 'Y') {
        printf("  Deletion cancelled.\n");
        pause_screen();
        return;
    }

    /* Shift records left */
    for (int i = idx; i < count - 1; i++)
        db[i] = db[i + 1];
    count--;

    printf(CLR_GREEN "  ✔  Record deleted. Remaining students: %d\n" CLR_RESET,
           count);
    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  6. CLASS RESULT (sorted by percentage, with rank)
 * ══════════════════════════════════════════════════════════ */
void class_result(void) {
    separator("CLASS RESULT");

    if (count == 0) {
        printf(CLR_YELLOW "  No records found.\n" CLR_RESET);
        pause_screen();
        return;
    }

    /* Copy indices and sort by percentage descending (bubble sort) */
    int idx[MAX_STUDENTS];
    for (int i = 0; i < count; i++) idx[i] = i;
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (db[idx[j]].percentage < db[idx[j+1]].percentage) {
                int tmp = idx[j]; idx[j] = idx[j+1]; idx[j+1] = tmp;
            }

    /* Stats */
    float total_pct = 0, max_pct = 0, min_pct = 200;
    int pass = 0;
    for (int i = 0; i < count; i++) {
        total_pct += db[i].percentage;
        if (db[i].percentage > max_pct) max_pct = db[i].percentage;
        if (db[i].percentage < min_pct) min_pct = db[i].percentage;
        if (db[i].grade != 'F') pass++;
    }

    printf("  Students: %d  |  Pass: %d  |  Fail: %d\n",
           count, pass, count - pass);
    printf("  Class Avg: %.2f%%  |  Highest: %.2f%%  |  Lowest: %.2f%%\n\n",
           total_pct / count, max_pct, min_pct);

    print_header(1);
    for (int i = 0; i < count; i++)
        print_row(i + 1, &db[idx[i]]);

    /* Grade distribution */
    int od=0,a=0,b=0,c=0,d=0,f=0;
    for (int i = 0; i < count; i++) {
        switch (db[i].grade) {
            case 'O': od++; break; case 'A': a++; break;
            case 'B': b++; break; case 'C': c++; break;
            case 'D': d++; break; case 'F': f++; break;
        }
    }
    printf(CLR_BOLD "\n  Grade Distribution: "
           "O=%d  A=%d  B=%d  C=%d  D=%d  F=%d\n" CLR_RESET,
           od, a, b, c, d, f);

    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  7. SAVE TO FILE
 * ══════════════════════════════════════════════════════════ */
void save_to_file(void) {
    separator("SAVE RECORDS");

    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf(CLR_RED "  [!] Cannot open file '%s' for writing.\n" CLR_RESET,
               DATA_FILE);
        pause_screen();
        return;
    }
    fwrite(&count, sizeof(int), 1, fp);
    fwrite(db, sizeof(Student), count, fp);
    fclose(fp);

    printf(CLR_GREEN "  ✔  %d record(s) saved to '%s'.\n" CLR_RESET,
           count, DATA_FILE);
    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  8. LOAD FROM FILE
 * ══════════════════════════════════════════════════════════ */
void load_from_file(void) {
    separator("LOAD RECORDS");

    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        printf(CLR_YELLOW "  [!] File '%s' not found. Starting fresh.\n" CLR_RESET,
               DATA_FILE);
        pause_screen();
        return;
    }

    int loaded;
    fread(&loaded, sizeof(int), 1, fp);
    if (loaded > MAX_STUDENTS) loaded = MAX_STUDENTS;
    fread(db, sizeof(Student), loaded, fp);
    fclose(fp);
    count = loaded;

    printf(CLR_GREEN "  ✔  %d record(s) loaded from '%s'.\n" CLR_RESET,
           count, DATA_FILE);
    pause_screen();
}

/* ══════════════════════════════════════════════════════════
 *  MAIN MENU
 * ══════════════════════════════════════════════════════════ */
void show_menu(void) {
    printf(CLR_CYAN
           "\n  ╔══════════════════════════════════════════════════════╗\n"
           "  ║       STUDENT RECORD MANAGEMENT SYSTEM              ║\n"
           "  ╠══════════════════════════════════════════════════════╣\n"
           CLR_RESET);
    printf("  ║  " CLR_GREEN "1." CLR_RESET "  Add New Student                               ║\n");
    printf("  ║  " CLR_GREEN "2." CLR_RESET "  Display All Records                          ║\n");
    printf("  ║  " CLR_GREEN "3." CLR_RESET "  Search Student by Roll Number                ║\n");
    printf("  ║  " CLR_GREEN "4." CLR_RESET "  Update Student Record                        ║\n");
    printf("  ║  " CLR_GREEN "5." CLR_RESET "  Delete Student Record                        ║\n");
    printf("  ║  " CLR_GREEN "6." CLR_RESET "  Class Result (Sorted by Marks)               ║\n");
    printf("  ║  " CLR_GREEN "7." CLR_RESET "  Save Records to File                         ║\n");
    printf("  ║  " CLR_GREEN "8." CLR_RESET "  Load Records from File                       ║\n");
    printf("  ║  " CLR_RED   "0." CLR_RESET "  Exit                                         ║\n");
    printf(CLR_CYAN
           "  ╚══════════════════════════════════════════════════════╝\n"
           CLR_RESET);
    printf("  Total students in memory: " CLR_BOLD "%d" CLR_RESET "\n", count);
    printf("\n  Enter your choice: ");
}

/* ══════════════════════════════════════════════════════════
 *  ENTRY POINT
 * ══════════════════════════════════════════════════════════ */
int main(void) {
    int choice;

    /* Auto-load saved data on startup */
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp) { fclose(fp); load_from_file(); }

    while (1) {
        clear_screen();
        show_menu();

        if (scanf("%d", &choice) != 1) { flush_stdin(); continue; }
        flush_stdin();

        switch (choice) {
            case 1: add_student();    break;
            case 2: display_all();    break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 6: class_result();   break;
            case 7: save_to_file();   break;
            case 8: load_from_file(); break;
            case 0:
                save_to_file();
                printf(CLR_GREEN
                       "\n  Records auto-saved. Goodbye!\n\n"
                       CLR_RESET);
                return 0;
            default:
                printf(CLR_RED "  [!] Invalid choice. Try 0-8.\n" CLR_RESET);
                pause_screen();
        }
    }
}