#include <stdio.h>
#include <time.h>

// Function to get days in a month
int getDaysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        return 29; // Leap year
    }
    return days[month - 1];
}

// Function to get day of week (0 = Sunday)
int getFirstDayOfMonth(int month, int year) {
    struct tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = 1;
    mktime(&t);
    return t.tm_wday;
}

// Function to print the calendar
void printCalendar(int month, int year) {
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};
    int days = getDaysInMonth(month, year);
    int startDay = getFirstDayOfMonth(month, year);

    printf("\n  ====== %s %d ======\n", months[month - 1], year);
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Print leading spaces
    for (int i = 0; i < startDay; i++) {
        printf("     ");
    }

    // Print days
    for (int day = 1; day <= days; day++) {
        printf("%4d ", day);
        if ((startDay + day) % 7 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");
}

int main() {
    int month, year;
    char choice;

    do {
        printf("=== Calendar Program ===\n");
        printf("1. View current month\n");
        printf("2. View specific month/year\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                time_t now = time(NULL);
                struct tm *tm = localtime(&now);
                printCalendar(tm->tm_mon + 1, tm->tm_year + 1900);
                break;
            }
            case '2':
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                if (month < 1 || month > 12) {
                    printf("Invalid month!\n");
                } else if (year < 1) {
                    printf("Invalid year!\n");
                } else {
                    printCalendar(month, year);
                }
                break;
            case '3':
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != '3');

    return 0;
}