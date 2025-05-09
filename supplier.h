#ifndef SUPPLIER_H
#define SUPPLIER_H

typedef struct {
    int id;
    char name[50];
    char contact[30];
} Supplier;

int isSupplierIdExists(int id);
void viewSuppliers();
void addSupplier();
void deleteSupplier();
void updateSupplier();

#endif