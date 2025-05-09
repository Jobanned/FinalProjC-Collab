#include "common.h"
#include "inventory.h"
#include "customer.h"

const char *monthname[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

int main() {
    loadInventoryFromFile(); // Load inventory before anything else
    customerMenu();          // Start directly in customer mode
    return 0;
}