#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    float subtotal;
} CartItem;

extern CartItem cart[100];
extern int cartCount;
extern float cartTotal;

void customerMenu();
void buyItem();
void customerSearch();
void addToCart();
void viewCart();
void checkout();

#endif