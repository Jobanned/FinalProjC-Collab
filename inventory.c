#include "common.h"
#include "inventory.h"
#include "ui.h"

InventoryNode* inventoryHead = NULL;

void loadInventoryFromFile() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("No existing inventory file found. Starting fresh.\n");
        return;
    }

    InventoryNode* temp;
    while (1) {
        temp = (InventoryNode*)malloc(sizeof(InventoryNode));
        if (fscanf(file, "%d %s %d %f", &temp->id, temp->name, &temp->quantity, &temp->price) != 4) {
            free(temp);
            break;
        }
        temp->next = inventoryHead;
        inventoryHead = temp;
    }

    fclose(file);
}

void saveInventoryToFile() {
    FILE *file = fopen("inventory.txt", "w");
    if (!file) {
        printf("Error opening file for writing!\n");
        return;
    }

    InventoryNode* temp = inventoryHead;
    while (temp) {
        fprintf(file, "%d %s %d %.2f\n", temp->id, temp->name, temp->quantity, temp->price);
        temp = temp->next;
    }

    fclose(file);
}

void viewInventory() {
    if (inventoryHead == NULL) {
        printf("\n=====================================\n");
        printf("      No inventory records found.\n");
        printf("=====================================\n");
        return;
    }

    printf("\n=====================================================================\n");
    printf("| %-5s | %-20s | %-10s | %-10s |\n", "ID", "Name", "Quantity", "Price");
    printf("=====================================================================\n");

    InventoryNode* temp = inventoryHead;
    while (temp != NULL) {
        printf("| %-5d | %-20s | %-10d | %-10.2f |\n", 
               temp->id, temp->name, temp->quantity, temp->price);
        temp = temp->next;
    }

    printf("=====================================================================\n");
}

int isItemIdExists(int id) {
    InventoryNode* temp = inventoryHead;
    while(temp != NULL) {
        if(temp->id == id) return 1;
        temp = temp->next;
    }
    return 0;
}

void addInventoryItem() {
    InventoryNode* newItem = (InventoryNode*)malloc(sizeof(InventoryNode));
    if (!newItem) {
        printf("Memory allocation failed!\n");
        return;
    }

    do {
        printf("Enter Item ID: ");
        scanf("%d", &newItem->id);
        clearInputBuffer();
        if(isItemIdExists(newItem->id)) {
            printf("Item ID already exists! Please enter a different ID.\n");
        }
    } while(isItemIdExists(newItem->id));
    
    printf("Enter Name: ");
    scanf("%s", newItem->name);
    printf("Enter Quantity: ");
    scanf("%d", &newItem->quantity);
    printf("Enter Price: ");
    scanf("%f", &newItem->price);

    newItem->next = inventoryHead;
    inventoryHead = newItem;

    saveInventoryToFile();
    printf("Item added successfully!\n");
    clearInputBuffer();
}

void deleteInventoryItem(int deleteID) {
    InventoryNode *temp = inventoryHead, *prev = NULL;

    if (temp != NULL && temp->id == deleteID) {
        inventoryHead = temp->next;
        free(temp);
        saveInventoryToFile();
        printf("Item deleted successfully!\n");
        return;
    }

    while (temp != NULL && temp->id != deleteID) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Item not found!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    saveInventoryToFile();
    printf("Item deleted successfully!\n");
}

void updateInventoryItem() {
    int id;
    printf("Enter Item ID to update: ");
    scanf("%d", &id);

    InventoryNode *temp = inventoryHead;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("Enter new Name: ");
            scanf("%s", temp->name);
            printf("Enter new Quantity: ");
            scanf("%d", &temp->quantity);
            printf("Enter new Price: ");
            scanf("%f", &temp->price);
            saveInventoryToFile();
            printf("Item updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Item not found!\n");
}
