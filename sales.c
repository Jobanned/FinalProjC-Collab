#include "common.h"
#include "sales.h"
#include "ui.h"

void viewSales() {
    FILE *file = fopen(FILE_SALES, "r");
    if (!file) {
        printf("No sales found!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    system("cls");
    displayWelcomeScreen();
    
    printf("\n=== ALL SALES ===\n");
    printf("ID\tItem\t\tQty\tTotal\tDate\n");
    printf("------------------------------------------------\n");
    
    Sale sale;
    while (fscanf(file, "%d %49s %d %f %19s", &sale.id, sale.itemName, 
                 &sale.quantitySold, &sale.totalPrice, sale.date) == 5) {
        printf("%d\t%-10s\t%d\t%.2f\t%s\n", 
              sale.id, sale.itemName, sale.quantitySold, sale.totalPrice, sale.date);
    }
    
    fclose(file);
    
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void generateSalesReport(const char *period) {
    FILE *file = fopen(FILE_SALES, "r");
    if (!file) {
        printf("Error opening sales file!\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    system("cls");
    displayWelcomeScreen();
    
    int targetYear, targetMonth, targetWeek;
    time_t now;
    struct tm *current;
    
    time(&now);
    current = localtime(&now);
    int currentYear = current->tm_year + 1900;
    int currentMonth = current->tm_mon + 1;

    if (strcmp(period, "Weekly") == 0) {
        printf("\nEnter year (e.g., 2023): ");
        scanf("%d", &targetYear);
        
        printf("Enter month (1-12): ");
        scanf("%d", &targetMonth);
        
        printf("Enter week of month (1-4): ");
        scanf("%d", &targetWeek);
        
        if (targetWeek < 1 || targetWeek > 4) {
            printf("Invalid week! Please enter 1-4.\n");
            printf("Press Enter to continue...");
            getchar();
            getchar();
            fclose(file);
            return;
        }
        
        int startDay = 1 + (targetWeek - 1) * 7;
        int endDay = startDay + 6;
        
        printf("\n=== WEEKLY SALES REPORT ===\n");
        printf("Week %d of %s %d (%d-%d %s)\n", 
              targetWeek, monthname[targetMonth-1], targetYear, 
              startDay, endDay, monthname[targetMonth-1]);
    }
    else if (strcmp(period, "Monthly") == 0) {
        printf("\nEnter year (e.g., 2023): ");
        scanf("%d", &targetYear);
        
        printf("Enter month (1-12): ");
        scanf("%d", &targetMonth);
        
        printf("\n=== MONTHLY SALES REPORT ===\n");
        printf("Month: %s %d\n", monthname[targetMonth-1], targetYear);
    }
    else if (strcmp(period, "Yearly") == 0) {
        printf("\nEnter year (e.g., 2023): ");
        scanf("%d", &targetYear);
        
        printf("\n=== YEARLY SALES REPORT ===\n");
        printf("Year: %d\n", targetYear);
    }
    
    clearInputBuffer();
    
    printf("ID\tItem\t\tQty\tTotal\tDate\n");
    printf("------------------------------------------------\n");
    
    Sale sale;
    float total = 0.0;
    int count = 0;
    
    while (fscanf(file, "%d %49s %d %f %19s", &sale.id, sale.itemName, 
                 &sale.quantitySold, &sale.totalPrice, sale.date) == 5) {
        int saleYear, saleMonth, saleDay;
        sscanf(sale.date, "%d-%d-%d", &saleYear, &saleMonth, &saleDay);
        
        int match = 0;
        if (strcmp(period, "Weekly") == 0) {
            int weekOfMonth = ((saleDay - 1) / 7) + 1;
            match = (saleYear == targetYear && 
                    saleMonth == targetMonth && 
                    weekOfMonth == targetWeek);
        }
        else if (strcmp(period, "Monthly") == 0) {
            match = (saleYear == targetYear && saleMonth == targetMonth);
        }
        else if (strcmp(period, "Yearly") == 0) {
            match = (saleYear == targetYear);
        }
        
        if (match) {
            printf("%d\t%-10s\t%d\t%.2f\t%s\n", 
                  sale.id, sale.itemName, sale.quantitySold, sale.totalPrice, sale.date);
            total += sale.totalPrice;
            count++;
        }
    }
    
    fclose(file);
    
    if (count == 0) {
        printf("\nNo sales found for the selected %s period.\n", period);
    } else {
        printf("------------------------------------------------\n");
        printf("Total Sales: %.2f\n", total);
        printf("Number of Transactions: %d\n", count);
    }
    
    printf("\nPress Enter to continue...");
    getchar();
}

void weeklySalesReport() { generateSalesReport("Weekly"); }
void monthlySalesReport() { generateSalesReport("Monthly"); }
void yearlySalesReport() { generateSalesReport("Yearly"); }

void generateReceipt(int id, char *itemName, int quantity, float total) {
    FILE *receipt = fopen("receipt.txt", "w");
    if (!receipt) {
        printf("Error creating receipt file!\n");
        return;
    }
    fprintf(receipt, "========== RECEIPT ==========\n");
    fprintf(receipt, "Item ID: %d\n", id);
    fprintf(receipt, "Item Name: %s\n", itemName);
    fprintf(receipt, "Quantity: %d\n", quantity);
    fprintf(receipt, "Total Price: %.2f\n", total);
    fprintf(receipt, "==============================\n");

    fclose(receipt);
    printf("\nReceipt generated! (Check 'receipt.txt')\n");
}