#include "common.h"
#include "supplier.h"
#include "ui.h"

int isSupplierIdExists(int id) {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    if (!file) {
        return 0;
    }

    Supplier sup;
    while (fscanf(file, "%d %49s %49s", &sup.id, sup.name, sup.contact) != EOF) {
        if (sup.id == id) {
            fclose(file);
            return 1;
        }
    }
    
    fclose(file);
    return 0;
}

void viewSuppliers() {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    if (!file) {
        printf("No supplier records found.\n");
        return;
    }

    Supplier sup;
    printf("\nID\tName\t\tContact\n");
    printf("--------------------------------\n");
    while (fscanf(file, "%d %s %s", &sup.id, sup.name, sup.contact) != EOF) {
        printf("%d\t%s\t\t%s\n", sup.id, sup.name, sup.contact);
    }

    fclose(file);
}

void addSupplier() {
    FILE *file = fopen(FILE_SUPPLIERS, "a");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Supplier sup;
    
    do {
        printf("Enter Supplier ID: ");
        scanf("%d", &sup.id);
        clearInputBuffer();
        
        if (isSupplierIdExists(sup.id)) {
            printf("Supplier ID %d already exists! Please enter a different ID.\n", sup.id);
        }
    } while (isSupplierIdExists(sup.id));

    printf("Enter Name: ");
    scanf("%49s", sup.name);
    clearInputBuffer();
    
    printf("Enter Contact: ");
    scanf("%49s", sup.contact);
    clearInputBuffer();

    fprintf(file, "%d %s %s\n", sup.id, sup.name, sup.contact);
    fclose(file);

    printf("Supplier added successfully!\n");
}

void deleteSupplier() {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    
    int targetId, found = 0;
    printf("Enter Supplier ID to delete: ");
    scanf("%d", &targetId);
    
    Supplier supplier;
    while (fscanf(file, "%d %49s %49s", &supplier.id, supplier.name, supplier.contact) != EOF) {
        if (supplier.id == targetId) {
            found = 1;
            continue;
        }
        fprintf(temp, "%d %s %s\n", supplier.id, supplier.name, supplier.contact);
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove(FILE_SUPPLIERS);
        rename("temp.txt", FILE_SUPPLIERS);
        printf("Supplier deleted successfully!\n");
    } else {
        printf("Supplier not found!\n");
    }
}

void updateSupplier() {
    FILE *file = fopen(FILE_SUPPLIERS, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    
    int targetId, found = 0;
    printf("Enter Supplier ID to update: ");
    scanf("%d", &targetId);
    
    Supplier supplier;
    while (fscanf(file, "%d %49s %49s", &supplier.id, supplier.name, supplier.contact) != EOF) {
        if (supplier.id == targetId) {
            found = 1;
            printf("Enter new Name: ");
            scanf("%s", supplier.name);
            printf("Enter new Contact: ");
            scanf("%s", supplier.contact);
        }
        fprintf(temp, "%d %s %s\n", supplier.id, supplier.name, supplier.contact);
    }
    
    fclose(file);
    fclose(temp);
    
    if (found) {
        remove(FILE_SUPPLIERS);
        rename("temp.txt", FILE_SUPPLIERS);
        printf("Supplier updated successfully!\n");
    } else {
        printf("Supplier not found!\n");
    }
}