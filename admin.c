#include "common.h"
#include "admin.h"
#include "inventory.h"
#include "supplier.h"
#include "sales.h"
#include "ui.h"
#include "customer.h"

int login() {
    char password[20] = {0};
    int i = 0;
    char ch;
    
    system("cls");
    displayWelcomeScreen();
    printf("Admin Login\n");
    printf("----------------------------\n");
    printf("Enter Password: ");
    
    while (1) {
        ch = getch();
        
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else if (ch == 27) {
            return 0;
        } else if (i < 19) {
            password[i++] = ch;
            printf("*");
        }
    }
    
    if (strcmp(password, "admin123") == 0) {
        printf("\nLogin successful! Press Enter to continue...");
        getch();
        return 1;
    } else {
        printf("\nIncorrect password! Press Enter to continue...");
        getch();
        return 0;
    }
}
void inventoryMenu() {
     const char *title = "Inventory Menu";
    const char *menuItems[] = {
        "View All Inventory",
        "Add Inventory Item",
        "Delete Inventory Item",
        "Update Inventory Item",
        "Back to Main Menu"
    };
    int menuCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selected = 0;
    int input;

    while (1) {
        displayMenuWithSelection(title, menuItems, menuCount, selected);
        
        input = getArrowKeyInput();
        
        switch(input) {
            case 1: // Up arrow
                selected = (selected > 0) ? selected - 1 : menuCount - 1;
                break;
            case 2: // Down arrow
                selected = (selected < menuCount - 1) ? selected + 1 : 0;
                break;
            case 3: // Enter key
                switch(selected) {
                    case 0:   viewInventory(); 
                              printf("\nPress Enter to continue...");
                              getchar();
                               break;
                    
                    case 1: addInventoryItem(); break;
                    case 2: 
                        printf("Enter Item ID to delete: ");
                        int id;
                        scanf("%d", &id);
                        deleteInventoryItem(id);
                        break;
                    case 3: updateInventoryItem(); break;
                    case 4: return; // Back to main menu
                }
                printf("\nPress Enter to continue...");
                getchar(); getchar();
                break;
            case 0: // Escape key
                return;
            default:
                break;
        }
    }
}
void salesMenu() {
    const char *title = "Sales Menu";
    const char *menuItems[] = {
        "View All Sales",
        "Weekly Sales Report",
        "Monthly Sales Report",
        "Yearly Sales Report",
        "Back to Main Menu"
    };
    int menuCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selected = 0;
    int input;

    while (1) {
        displayMenuWithSelection(title, menuItems, menuCount, selected);
        
        input = getArrowKeyInput();
        
        switch(input) {
            case 1: // Up arrow
                selected = (selected > 0) ? selected - 1 : menuCount - 1;
                break;
            case 2: // Down arrow
                selected = (selected < menuCount - 1) ? selected + 1 : 0;
                break;
            case 3: // Enter key
                switch(selected) {
                    case 0: viewSales(); break;
                    case 1: weeklySalesReport(); break;
                    case 2: monthlySalesReport(); break;
                    case 3: yearlySalesReport(); break;
                    case 4: return; // Back to main menu
                }
                printf("\nPress Enter to continue...");
                getchar(); getchar();
                break;
            case 0: // Escape key
                return;
            default:
                break;
        }
    }
}
void supplierMenu() {
    const char *title = "Supplier Menu";
    const char *menuItems[] = {
        "View All Suppliers",
        "Add Supplier",
        "Delete Supplier",
        "Update Supplier",
        "Back to Main Menu"
    };
    int menuCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selected = 0;
    int input;

    while (1) {
        displayMenuWithSelection(title, menuItems, menuCount, selected);
        
        input = getArrowKeyInput();
        
        switch(input) {
            case 1: // Up arrow
                selected = (selected > 0) ? selected - 1 : menuCount - 1;
                break;
            case 2: // Down arrow
                selected = (selected < menuCount - 1) ? selected + 1 : 0;
                break;
            case 3: // Enter key
                switch(selected) {
                    case 0: viewSuppliers(); break;
                    case 1: addSupplier(); break;
                    case 2: deleteSupplier(); break;
                    case 3: updateSupplier(); break;
                    case 4: return; // Back to main menu
                }
                printf("\nPress Enter to continue...");
                getchar(); getchar();
                break;
            case 0: // Escape key
                return;
            default:
                break;
        }
    }
}
void adminMenu() {
    const char *title = "Admin Menu";
    const char *menuItems[] = {
        "Search",
        "Inventory",
        "Suppliers",
        "Sales",
        "Back to Customer Menu"
    };
    int menuCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selected = 0;
    int input;

    while (1) {
        displayMenuWithSelection(title, menuItems, menuCount, selected);
        
        input = getArrowKeyInput();
        
        switch(input) {
            case 1: // Up arrow
                selected = (selected > 0) ? selected - 1 : menuCount - 1;
                break;
            case 2: // Down arrow
                selected = (selected < menuCount - 1) ? selected + 1 : 0;
                break;
            case 3: // Enter key
                switch(selected) {
                    case 0: searchByName(); break;
                    case 1: inventoryMenu(); 
                             printf("\nPress Enter to continue...");
                             getchar();
                             break;
                    case 2: supplierMenu(); break;
                    case 3: salesMenu(); break;
                    case 4: return;
                }
                break;
            case 0: // Escape key
                return;
            default:
                break;
        }
    }
}

void searchInventoryByName() {
    if (inventoryHead == NULL) {
        printf("\nNo inventory records found.\n");
        return;
    }

    char searchName[50];
    printf("\nEnter item name to search: ");
    scanf("%49s", searchName);
    clearInputBuffer();
    
    printf("\nSearch Results for '%s':\n", searchName);
    printf("========================================\n");
    
    InventoryNode* temp = inventoryHead;
    int found = 0;

    while (temp != NULL) {
        if(strstr(strToLower(temp->name), strToLower(searchName)) != NULL) {
            printf("ID: %-5d | Name: %-20s | Qty: %-5d | Price: %-8.2f\n", 
                  temp->id, temp->name, temp->quantity, temp->price);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No matching items found.\n");
    }
}

void searchInventoryByID() {
    if (inventoryHead == NULL) {
        printf("\nNo inventory records found.\n");
        return;
    }

    int searchID;
    printf("\nEnter item ID to search: ");
    scanf("%d", &searchID);
    clearInputBuffer();
    
    printf("\nSearch Results for ID '%d':\n", searchID);
    printf("========================================\n");
    
    InventoryNode* temp = inventoryHead;
    int found = 0;

    while (temp != NULL) {
        if(temp->id == searchID) {
            printf("ID: %-5d | Name: %-20s | Qty: %-5d | Price: %-8.2f\n", 
                  temp->id, temp->name, temp->quantity, temp->price);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No item with ID %d found.\n", searchID);
    }
}

void searchSupplierByName() {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    if (!file) {
        printf("\nNo supplier records found.\n");
        return;
    }

    char searchName[50];
    printf("\nEnter supplier name to search: ");
    scanf("%49s", searchName);
    clearInputBuffer();
    
    printf("\nSearch Results for '%s':\n", searchName);
    printf("========================================\n");
    
    Supplier supplier;
    int found = 0;

    while (fscanf(file, "%d %49s %49s", &supplier.id, supplier.name, supplier.contact) != EOF) {
        if(strstr(strToLower(supplier.name), strToLower(searchName)) != NULL) {
            printf("ID: %-5d | Name: %-20s | Contact: %-15s\n", 
                  supplier.id, supplier.name, supplier.contact);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("No matching suppliers found.\n");
    }
}

void searchSupplierByID() {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    if (!file) {
        printf("\nNo supplier records found.\n");
        return;
    }

    int searchID;
    printf("\nEnter supplier ID to search: ");
    scanf("%d", &searchID);
    clearInputBuffer();
    
    printf("\nSearch Results for ID '%d':\n", searchID);
    printf("========================================\n");
    
    Supplier supplier;
    int found = 0;

    while (fscanf(file, "%d %49s %49s", &supplier.id, supplier.name, supplier.contact) != EOF) {
        if(supplier.id == searchID) {
            printf("ID: %-5d | Name: %-20s | Contact: %-15s\n", 
                  supplier.id, supplier.name, supplier.contact);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("No supplier with ID %d found.\n", searchID);
    }
}

void searchByName() {
    const char *title = "Search Options";
    const char *menuItems[] = {
        "Search Inventory by Name",
        "Search Inventory by ID",
        "Search Supplier by Name",
        "Search Supplier by ID",
        "Back to Menu"
    };
    int menuCount = sizeof(menuItems)/sizeof(menuItems[0]);
    int selected = 0;
    int input;

    while (1) {
        displayMenuWithSelection(title, menuItems, menuCount, selected);
        
        input = getArrowKeyInput();
        
        switch(input) {
            case 1: // Up arrow
                selected = (selected > 0) ? selected - 1 : menuCount - 1;
                break;
            case 2: // Down arrow
                selected = (selected < menuCount - 1) ? selected + 1 : 0;
                break;
            case 3: // Enter key
                switch(selected) {
                    case 0: searchInventoryByName(); break;
                    case 1: searchInventoryByID(); break;
                    case 2: searchSupplierByName(); break;
                    case 3: searchSupplierByID(); break;
                    case 4: return;
                }
                printf("\nPress Enter to continue...");
                getchar(); getchar();
                break;
            case 0: // Escape key
                return;
            default:
                break;
        }
    }
}