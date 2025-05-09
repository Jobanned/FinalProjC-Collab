#include "common.h"
#include "inventory.h"
#include "customer.h"
#include "sales.h"
#include "ui.h"
#include "admin.h"

CartItem cart[100];
int cartCount = 0;
float cartTotal = 0.0;

void customerMenu() {
    const char *title = "Customer Menu";
    const char *menuItems[] = {
        "Search for Product",
        "View Items",
        "Buy Item",
        "Log in as Admin",
        "Exit"
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
                    case 0: customerSearch(); break;
                    case 1: viewInventory(); 
                            printf("\nPress Enter to continue...");
                            getchar();
                            break;
                    case 2: buyItem();
                            printf("\nPress Enter to continue...");
                            getchar();
                            break;
                    case 3: 
                        if (login() == 1) {
                            adminMenu();
                        }
                        break;
                    case 4: 
                        printf("Goodbye!\n");
                        exit(0);
                }
                break;
            case 0: // Escape key
            case 4: // Left arrow
            case 5: // Right arrow
            default:
                break;
        }
    }
}

void buyItem() {
    system("cls");
    displayWelcomeScreen();
    const char *title = "\n=== SHOPPING CART ===\n";
    const char *menuItems[] = {
        "Add Item to Cart",
        "View Cart",
        "Checkout",
        "Cancel Purchase"
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
                    case 0: addToCart(); break;
                    case 1: viewCart(); break;
                    case 2: checkout(); break;
                    case 3: 
                        cartCount = 0; 
                        cartTotal = 0.0;
                        printf("\nPurchase cancelled. Press Enter to continue...");
                        getchar();
                        return;
                }
                break;
            case 0: // Escape key
            case 4: // Left arrow
            case 5: // Right arrow
            default:
                break;
        }
    }
}

void customerSearch() {
    if (inventoryHead == NULL) {
        printf("\nNo inventory records found.\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }
    
    char searchName[50];
    printf("\n\nEnter item name to search: ");
    scanf("%49s", searchName);
    getchar();
    
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
    
    printf("\nPress Enter to continue...");
    getchar();
}

void addToCart() {
    system("cls");
    displayWelcomeScreen();
    
    int id, qty;
    InventoryNode* temp = inventoryHead;
    
    printf("\nCURRENT INVENTORY:\n");
    viewInventory();
    
    printf("\nEnter Item ID to add to cart (0 to cancel): ");
    if(scanf("%d", &id) != 1 || id == 0) {
        printf("Cancelled. Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    temp = inventoryHead;
    while(temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    
    if(temp == NULL) {
        printf("\nItem not found! Press Enter to continue...");
        getchar(); getchar();
        return;
    }
    
    printf("\nSelected Item: %s (Available: %d)\n", temp->name, temp->quantity);
    printf("Enter quantity to purchase: ");
    scanf("%d", &qty);
    
    if(qty <= 0 || qty > temp->quantity) {
        printf("Invalid quantity! Available: %d. Press Enter...", temp->quantity);
        getchar(); getchar();
        return;
    }
    
    for(int i = 0; i < cartCount; i++) {
        if(cart[i].id == id) {
            cart[i].quantity += qty;
            cart[i].subtotal += qty * temp->price;
            cartTotal += qty * temp->price;
            printf("\nUpdated quantity in cart. Press Enter to continue...");
            getchar(); getchar();
            return;
        }
    }
    
    if(cartCount < 100) {
        cart[cartCount].id = temp->id;
        strcpy(cart[cartCount].name, temp->name);
        cart[cartCount].quantity = qty;
        cart[cartCount].price = temp->price;
        cart[cartCount].subtotal = qty * temp->price;
        cartTotal += cart[cartCount].subtotal;
        cartCount++;
        
        printf("\nItem added to cart! Press Enter to continue...");
        getchar(); getchar();
    } else {
        printf("\nCart is full! Press Enter to continue...");
        getchar(); getchar();
    }
}

void viewCart() {
    system("cls");
    displayWelcomeScreen();
    
    printf("\n=== YOUR SHOPPING CART ===\n");
    printf("ID\tName\t\tQty\tPrice\tSubtotal\n");
    printf("------------------------------------------------\n");
    
    for(int i = 0; i < cartCount; i++) {
        printf("%d\t%-15s\t%d\t%.2f\t%.2f\n", 
              cart[i].id, cart[i].name, cart[i].quantity, 
              cart[i].price, cart[i].subtotal);
    }
    
    printf("------------------------------------------------\n");
    printf("TOTAL: %.2f\n", cartTotal);
    printf("\nPress Enter to continue shopping...");
    getchar();
}

void checkout() {
    system("cls");
    displayWelcomeScreen();
    
    if(cartCount == 0) {
        printf("\nYour cart is empty! Press Enter to continue...");
        getchar();
        return;
    }
    
    printf("\n=== CART SUMMARY ===\n");
    printf("ID\tName\t\tQty\tSubtotal\n");
    printf("--------------------------------------------\n");
    
    for(int i = 0; i < cartCount; i++) {
        printf("%d\t%-15s\t%d\t%.2f\n", 
              cart[i].id, cart[i].name, cart[i].quantity, cart[i].subtotal);
    }
    
    printf("--------------------------------------------\n");
    printf("TOTAL: %.2f\n\n", cartTotal);
    
    float payment;
    do {
        printf("Enter payment amount: ");
        scanf("%f", &payment);
        clearInputBuffer();
        
        if(payment < cartTotal) {
            printf("Insufficient payment! Please enter at least %.2f\n", cartTotal);
        }
    } while(payment < cartTotal);
    
    float change = payment - cartTotal;
    printf("\nChange: %.2f\n", change);
    
    char receiptChoice;
    printf("\nWould you like a receipt? (y/n): ");
    scanf(" %c", &receiptChoice);
    clearInputBuffer();
    
    time_t now;
    time(&now);
    
    for(int i = 0; i < cartCount; i++) {
        InventoryNode* temp = inventoryHead;
        while(temp != NULL && temp->id != cart[i].id) {
            temp = temp->next;
        }
        
        if(temp != NULL) {
            temp->quantity -= cart[i].quantity;
            
            FILE* saleFile = fopen(FILE_SALES, "a");
            if(saleFile) {
                char dateStr[20];
                strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", localtime(&now));
                fprintf(saleFile, "%d %s %d %.2f %s\n", 
                       cart[i].id, cart[i].name, cart[i].quantity, 
                       cart[i].subtotal, dateStr);
                fclose(saleFile);
            }
        }
    }
    
    saveInventoryToFile();
    
    if(tolower(receiptChoice) == 'y') {
        FILE* receiptFile = fopen("receipt.txt", "w");
        if(receiptFile) {
            fprintf(receiptFile, "=== RECEIPT ===\n");
            fprintf(receiptFile, "Date: %s", ctime(&now));
            fprintf(receiptFile, "--------------------------------\n");
            
            for(int i = 0; i < cartCount; i++) {
                fprintf(receiptFile, "%s x%d @%.2f = %.2f\n", 
                       cart[i].name, cart[i].quantity, 
                       cart[i].price, cart[i].subtotal);
            }
            
            fprintf(receiptFile, "--------------------------------\n");
            fprintf(receiptFile, "TOTAL: %.2f\n", cartTotal);
            fprintf(receiptFile, "PAID: %.2f\n", payment);
            fprintf(receiptFile, "CHANGE: %.2f\n", change);
            fprintf(receiptFile, "================================\n");
            fprintf(receiptFile, "Thank you for your purchase!\n");
            
            fclose(receiptFile);
            printf("\nReceipt saved to 'receipt.txt'\n");
        } else {
            printf("\nError creating receipt file!\n");
        }
    }
    
    cartCount = 0;
    cartTotal = 0.0;
    
    printf("\nThank you for your purchase! Press Enter to continue...");
    getchar();
}