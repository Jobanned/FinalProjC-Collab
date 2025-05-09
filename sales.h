#ifndef SALES_H
#define SALES_H

typedef struct {
    int id;
    char itemName[50];
    int quantitySold;
    float totalPrice;
    char date[20];
    float amount;
} Sale;

void viewSales();
void weeklySalesReport();
void monthlySalesReport();
void yearlySalesReport();
void generateSalesReport(const char *period);
void generateReceipt(int id, char *itemName, int quantity, float total);

#endif