// A simple program to track your daily tasks

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 50          // limit of tasks I can store
#define NAME_SIZE 30          // Max length of task name
#define DESC_SIZE 80          // Max length of description

struct Task {
    int number;              
    char name[NAME_SIZE];    // What to do
    char note[DESC_SIZE];    // Extra details
    int hour;                // What hour? (0-23)
    int min;                 // What minute? (0-59)
    int how_long;            // How many minutes
    int done;                // 1 = done, 0 = not done
    int y, m, d;             // Date (year, month, day)
};


// ============================================
// STRUCTURE: Holds all your tasks
// ============================================
struct TaskList {
    struct Task tasks[MAX_TASKS];
    int total;               // How many tasks you have
};


// --------------------------------------------
// Initialize - set up empty list
// --------------------------------------------
void startList(struct TaskList *list) {
    list->total = 0;
}


// --------------------------------------------
// Add a new task
// --------------------------------------------
void addTask(struct TaskList *list) {
    if (list->total >= MAX_TASKS) {
        printf("\n>> Sorry! Can't add more tasks. Delete some first.\n");
        return;
    }
    
    struct Task *t = &list->tasks[list->total];
    
    printf("\n--- ADD NEW TASK ---\n");
    printf("What do you need to do? ");
    scanf(" %[^\n]", t->name);
    printf("Any notes? (optional) ");
    scanf(" %[^\n]", t->note);
    printf("Year? (e.g., 2026) ");
    scanf("%d", &t->y);
    printf("Month? (1-12) ");
    scanf("%d", &t->m);
    printf("Day? ");
    scanf("%d", &t->d);
    printf("What time? (hour 0-23) ");
    scanf("%d", &t->hour);
    printf("Minutes? (0-59) ");
    scanf("%d", &t->min);
    printf("How long? (minutes) ");
    scanf("%d", &t->how_long);
    
    t->number = list->total + 1;
    t->done = 0;
    list->total++;
    
    printf("\n>> Task added! Good luck! :)\n");
}


// --------------------------------------------
// Mark task as done
// --------------------------------------------
void markDone(struct TaskList *list) {
    int id;
    printf("\n--- MARK AS DONE ---\n");
    printf("Which task number? ");
    scanf("%d", &id);
    
    for (int i = 0; i < list->total; i++) {
        if (list->tasks[i].number == id) {
            list->tasks[i].done = 1;
            printf("\n>> Nice! '%s' is done! Great job!\n", list->tasks[i].name);
            return;
        }
    }
    printf("\n>> Task not found. Check the number and try again.\n");
}


// --------------------------------------------
// Delete a task
// --------------------------------------------
void deleteTask(struct TaskList *list) {
    int id;
    printf("\n--- DELETE TASK ---\n");
    printf("Which task number to delete? ");
    scanf("%d", &id);
    
    for (int i = 0; i < list->total; i++) {
        if (list->tasks[i].number == id) {
            // Move all tasks after this one forward
            for (int j = i; j < list->total - 1; j++) {
                list->tasks[j] = list->tasks[j + 1];
            }
            list->total--;
            printf("\n>> Task deleted.\n");
            return;
        }
    }
    printf("\n>> Task not found.\n");
}


// --------------------------------------------
// Show tasks for TODAY
// --------------------------------------------
void showToday(struct TaskList *list) {
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    int yr = today->tm_year + 1900;
    int mo = today->tm_mon + 1;
    int da = today->tm_mday;
    
    printf("\n========================================");
    printf("\n   TODAY'S TASKS - %d/%d/%d", mo, da, yr);
    printf("\n========================================\n");
    
    int found = 0;
    for (int i = 0; i < list->total; i++) {
        struct Task *t = &list->tasks[i];
        if (t->y == yr && t->m == mo && t->d == da) {
            printf("\n[%d] %s", t->number, t->name);
            printf("\n    Time: %02d:%02d", t->hour, t->min);
            printf("\n    Duration: %d min", t->how_long);
            printf("\n    Note: %s", t->note);
            printf("\n    Status: %s\n", t->done ? "DONE! :D" : "Not done yet");
            found = 1;
        }
    }
    
    if (!found) {
        printf("\n>> No tasks for today! Enjoy your free time!\n");
    }
}


// --------------------------------------------
// Show tasks for any day
// --------------------------------------------
void showDay(struct TaskList *list) {
    int yr, mo, da;
    printf("\n--- VIEW SPECIFIC DAY ---\n");
    printf("Year? ");
    scanf("%d", &yr);
    printf("Month? (1-12) ");
    scanf("%d", &mo);
    printf("Day? ");
    scanf("%d", &da);
    
    printf("\n========================================");
    printf("\n   TASKS FOR %d/%d/%d", mo, da, yr);
    printf("\n========================================\n");
    
    int found = 0;
    for (int i = 0; i < list->total; i++) {
        struct Task *t = &list->tasks[i];
        if (t->y == yr && t->m == mo && t->d == da) {
            printf("\n[%d] %s", t->number, t->name);
            printf("\n    Time: %02d:%02d", t->hour, t->min);
            printf("\n    Duration: %d min", t->how_long);
            printf("\n    Note: %s", t->note);
            printf("\n    Status: %s\n", t->done ? "DONE! :D" : "Not done yet");
            found = 1;
        }
    }
    
    if (!found) {
        printf("\n>> No tasks for this day!\n");
    }
}


// --------------------------------------------
// Show ALL tasks
// --------------------------------------------
void showAll(struct TaskList *list) {
    printf("\n========================================");
    printf("\n       ALL YOUR TASKS");
    printf("\n========================================\n");
    
    if (list->total == 0) {
        printf("\n>> No tasks yet! Add some below :)\n");
        return;
    }
    
    for (int i = 0; i < list->total; i++) {
        struct Task *t = &list->tasks[i];
        printf("\n[%d] %s", t->number, t->name);
        printf("\n    Date: %d/%d/%d", t->m, t->d, t->y);
        printf("\n    Time: %02d:%02d", t->hour, t->min);
        printf("\n    Duration: %d min", t->how_long);
        printf("\n    Note: %s", t->note);
        printf("\n    Status: %s\n", t->done ? "DONE! :D" : "Not done yet");
    }
}


// --------------------------------------------
// Show today's summary
// --------------------------------------------
void todaySummary(struct TaskList *list) {
    time_t now = time(NULL);
    struct tm *today = localtime(&now);
    int yr = today->tm_year + 1900;
    int mo = today->tm_mon + 1;
    int da = today->tm_mday;
    
    int total = 0, done = 0;
    
    for (int i = 0; i < list->total; i++) {
        struct Task *t = &list->tasks[i];
        if (t->y == yr && t->m == mo && t->d == da) {
            total++;
            if (t->done) done++;
        }
    }
    
    printf("\n========================================");
    printf("\n      TODAY'S SUMMARY");
    printf("\n========================================");
    printf("\nDate: %d/%d/%d", mo, da, yr);
    printf("\nTotal tasks: %d", total);
    printf("\nDone: %d", done);
    printf("\nLeft: %d", total - done);
    
    if (total == 0) {
        printf("\n\n>> You have no tasks today! Relax! :)\n");
    } else if (done == total) {
        printf("\n\n>> ALL DONE! You're awesome! :D\n");
    } else {
        printf("\n\n>> Keep going! You can do it!\n");
    }
    printf("========================================\n");
}


// --------------------------------------------
// Main menu
// --------------------------------------------
void menu() {
    printf("\n========================================");
    printf("\n      STUDENT TASK MANAGER");
    printf("\n========================================");
    printf("\n1. Add a new task");
    printf("\n2. See today's tasks");
    printf("\n3. See tasks for a specific day");
    printf("\n4. See ALL tasks");
    printf("\n5. Mark task as done");
    printf("\n6. Delete a task");
    printf("\n7. Today's summary");
    printf("\n8. Exit");
    printf("\n========================================");
    printf("\nPick one: ");
}


// ============================================
// MAIN PROGRAM
// ============================================
int main() {
    struct TaskList myList;
    startList(&myList);
    
    // Get today's date
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int thisYear = t->tm_year + 1900;
    int thisMonth = t->tm_mon + 1;
    int thisDay = t->tm_mday;
    
    // Add some sample tasks for today (so it's not empty)
    struct Task sample1 = {1, "Morning class", "Don't be late!", 9, 0, 60, 0, thisYear, thisMonth, thisDay};
    struct Task sample2 = {2, "Study session", "Library at 2pm", 14, 0, 120, 0, thisYear, thisMonth, thisDay};
    struct Task sample3 = {3, "Assignment due", "Submit online", 23, 59, 0, 0, thisYear, thisMonth, thisDay};
    
    myList.tasks[0] = sample1;
    myList.tasks[1] = sample2;
    myList.tasks[2] = sample3;
    myList.total = 3;
    
    int choice;
    
    printf("\n========================================");
    printf("\n   Welcome to Student Task Manager!");
    printf("\n   Let's get organized! :D");
    printf("\n========================================\n");
    
    while (1) {
        menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addTask(&myList);
                break;
            case 2:
                showToday(&myList);
                break;
            case 3:
                showDay(&myList);
                break;
            case 4:
                showAll(&myList);
                break;
            case 5:
                markDone(&myList);
                break;
            case 6:
                deleteTask(&myList);
                break;
            case 7:
                todaySummary(&myList);
                break;
            case 8:
                printf("\n>> Bye! Have a great day! :)\n");
                return 0;
            default:
                printf("\n>> Invalid choice. Try again!\n");
        }
    }
    
    return 0;
}