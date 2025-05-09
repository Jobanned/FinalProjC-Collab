#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct InventoryNode {
    int id;
    char name[50];
    int quantity;
    float price;
    struct InventoryNode* next;
} InventoryNode;

extern InventoryNode* inventoryHead;

void loadInventoryFromFile();
void saveInventoryToFile();
void viewInventory();
int isItemIdExists(int id);
void addInventoryItem();
void deleteInventoryItem(int deleteID);
void updateInventoryItem();


#endif