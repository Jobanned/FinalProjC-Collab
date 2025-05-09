#ifndef UI_H
#define UI_H

void displayWelcomeScreen();
void displayMainMenu();
int getArrowKeyInput();
void displayMenuWithSelection(const char *title, const char **items, int count, int selected);
void clearInputBuffer();
char* strToLower(char* str);

#endif