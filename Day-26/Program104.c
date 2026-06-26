#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUESTIONS 10
#define MAX_LEN       300
#define MAX_OPT       100

/* ── Data structure ── */
typedef struct {
    char question[MAX_LEN];
    char options[4][MAX_OPT];
    int  correct;   /* 1-based index of the correct option */
} Question;

/* ── Question bank ── */
Question bank[MAX_QUESTIONS] = {
    {
        "What does CPU stand for?",
        {"Central Processing Unit", "Central Program Utility",
         "Computer Personal Unit", "Core Processing Unit"},
        1
    },
    {
        "Which data structure uses FIFO ordering?",
        {"Stack", "Queue", "Tree", "Graph"},
        2
    },
    {
        "What is the time complexity of binary search?",
        {"O(n)", "O(n^2)", "O(log n)", "O(n log n)"},
        3
    },
    {
        "Which language is known as the mother of all languages?",
        {"Python", "Java", "C", "Assembly"},
        3
    },
    {
        "What does RAM stand for?",
        {"Read Access Memory", "Random Access Memory",
         "Run-time Application Memory", "Rapid Access Module"},
        2
    },
    {
        "Which sorting algorithm has the best average-case complexity?",
        {"Bubble Sort", "Selection Sort", "Insertion Sort", "Quick Sort"},
        4
    },
    {
        "What symbol is used for single-line comments in C?",
        {"#", "//", "/* */", "--"},
        2
    },
    {
        "Which of these is NOT a primitive data type in C?",
        {"int", "float", "string", "char"},
        3
    },
    {
        "What does HTTP stand for?",
        {"HyperText Transfer Protocol", "High Transfer Text Protocol",
         "Hyper Transfer Technology Protocol", "HyperText Transmission Path"},
        1
    },
    {
        "What is the output of: printf(\"%d\", 5 / 2); in C?",
        {"2.5", "2", "3", "Compile error"},
        2
    }
};

/* ── Helpers ── */
void print_separator(void) {
    printf("\n%s\n", "============================================================");
}

void print_question(int num, Question *q) {
    printf("\nQ%d: %s\n", num, q->question);
    for (int i = 0; i < 4; i++) {
        printf("  %d. %s\n", i + 1, q->options[i]);
    }
}

int get_answer(void) {
    int ans;
    while (1) {
        printf("Your answer (1-4): ");
        if (scanf("%d", &ans) == 1 && ans >= 1 && ans <= 4)
            return ans;
        printf("  [!] Invalid input. Please enter a number between 1 and 4.\n");
        while (getchar() != '\n'); /* flush input buffer */
    }
}

void show_result(int score, int total) {
    float pct = (float)score / total * 100.0f;
    print_separator();
    printf("           *** QUIZ COMPLETE ***\n");
    print_separator();
    printf("  Score : %d / %d  (%.1f%%)\n", score, total, pct);

    if      (pct == 100) printf("  Grade : A+  |  Perfect score! Outstanding!\n");
    else if (pct >= 80)  printf("  Grade : A   |  Excellent work!\n");
    else if (pct >= 60)  printf("  Grade : B   |  Good job, keep practising.\n");
    else if (pct >= 40)  printf("  Grade : C   |  Fair attempt, review the topics.\n");
    else                 printf("  Grade : F   |  Keep studying — you'll get there!\n");

    print_separator();
}

/* ── Main ── */
int main(void) {
    int score = 0;
    char again;

    print_separator();
    printf("          Welcome to the C Quiz Application!\n");
    print_separator();
    printf("  Rules:\n");
    printf("   * %d multiple-choice questions\n", MAX_QUESTIONS);
    printf("   * Enter the option number (1-4) for each answer\n");
    printf("   * Your score is shown at the end\n");
    print_separator();
    printf("\nPress ENTER to start...");
    while (getchar() != '\n');

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        print_question(i + 1, &bank[i]);

        int ans = get_answer();

        if (ans == bank[i].correct) {
            printf("  ✔  Correct!\n");
            score++;
        } else {
            printf("  ✘  Wrong! Correct answer: %d. %s\n",
                   bank[i].correct,
                   bank[i].options[bank[i].correct - 1]);
        }
    }

    show_result(score, MAX_QUESTIONS);

    printf("\nWould you like to play again? (y/n): ");
    scanf(" %c", &again);
    if (again == 'y' || again == 'Y') {
        score = 0;
        /* restart by re-running main — simple recursion for small programs */
        return main();
    }

    printf("\nThanks for playing! Goodbye.\n\n");
    return 0;
}