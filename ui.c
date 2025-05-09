#include "common.h"
#include "ui.h"

void displayWelcomeScreen() {
    printf("\n==========================================\n");
    printf("Livestock Supply Chain Management System\n");
    printf("==========================================\n\n");
}

void displayMainMenu() {
    printf("1. Search\n");
    printf("2. Inventory\n");
    printf("3. Suppliers\n");
    printf("4. Sales\n");
    printf("0. Exit\n");
}

int getArrowKeyInput() {
    int ch = getch();
    if (ch == 0 || ch == 224) {
        switch(getch()) {
            case 72: return 1;    // Up arrow
            case 80: return 2;    // Down arrow
            case 13: return 3;   // Enter key
            case 27: return 0;   // Escape key
            default: return -1;
        }
    }
    else if (ch == 13) return 3;
    return -1;
}

void displayMenuWithSelection(const char *title, const char **items, int count, int selected) {
    system("cls");
    displayWelcomeScreen();
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    printf("\n%s\n", title);
    printf("----------------------------\n");
    
    for (int i = 0; i < count; i++) {
        if (i == selected) {
            SetConsoleTextAttribute(hConsole, 112);
            printf("> %s", items[i]);
            SetConsoleTextAttribute(hConsole, 7);
            printf("\n");
        } else {
            printf("  %s\n", items[i]);
        }
    }
    printf("----------------------------\n");
    printf("Use arrow keys to navigate | Enter to select \n");
}

void clearInputBuffer() {
    while(getchar() != '\n');
}

char* strToLower(char* str) {
    for(char *p = str; *p; p++) *p = tolower(*p);
    return str;
}