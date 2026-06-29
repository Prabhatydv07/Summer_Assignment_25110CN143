/*
 * ================================================================
 *   INVENTORY MANAGEMENT SYSTEM IN C
 * ================================================================
 *
 *  Features:
 *   1.  Add new product
 *   2.  Display all products
 *   3.  Search product (by ID or Name)
 *   4.  Update product details
 *   5.  Delete product
 *   6.  Update stock (restock / sell)
 *   7.  Display low-stock alerts  (qty < threshold)
 *   8.  Sort products (by Name / Price / Quantity)
 *   9.  Display category-wise summary
 *  10.  Generate inventory report (total value, counts)
 *  11.  Save inventory to file
 *  12.  Load inventory from file
 *  13.  Exit
 *
 *  Data is saved to "inventory.dat" so it persists between runs.
 * ================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   /* only for strcmp / strstr / strcpy in file I/O helpers */

/* ── Constants ──────────────────────────────────────────────── */
#define MAX_PRODUCTS   200          /* Maximum number of products */
#define NAME_LEN        50          /* Max length of product name */
#define CAT_LEN         30          /* Max length of category     */
#define DATA_FILE      "inventory.dat"
#define LOW_STOCK_THRESH 10         /* Alert if quantity < this   */

/* ================================================================
 *  DATA STRUCTURE  — one record per product
 * ================================================================ */
typedef struct {
    int    id;                  /* Unique product ID              */
    char   name[NAME_LEN];      /* Product name                   */
    char   category[CAT_LEN];   /* e.g. Electronics, Food, ...    */
    int    quantity;            /* Units currently in stock       */
    double price;               /* Price per unit (INR or any)    */
    double costPrice;           /* Cost price (for profit calc)   */
} Product;

/* ── Global inventory array & counter ──────────────────────── */
Product inventory[MAX_PRODUCTS];  /* All products live here       */
int     productCount = 0;         /* How many products are stored */
int     nextID       = 1000;      /* Auto-increment product ID    */

/* ================================================================
 *  HELPER FUNCTIONS
 * ================================================================ */

/* Clears leftover characters from the input buffer.
 * Prevents scanf failures and infinite loops.                    */
void flushInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Reads a full line (including spaces) safely into str.          */
void readLine(char str[], int maxLen)
{
    int i = 0, c;
    while (i < maxLen - 1 && (c = getchar()) != '\n' && c != EOF)
        str[i++] = (char)c;
    str[i] = '\0';
}

/* Converts string to lowercase for case-insensitive search.      */
void strToLower(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0') {
        char c = src[i];
        dest[i] = (c >= 'A' && c <= 'Z') ? c + 32 : c;
        i++;
    }
    dest[i] = '\0';
}

/* Checks if needle exists inside haystack (case-insensitive).    */
int containsStr(const char *haystack, const char *needle)
{
    char h[NAME_LEN * 2], n[NAME_LEN * 2];
    strToLower(h, haystack);
    strToLower(n, needle);
    return strstr(h, n) != NULL;
}

/* Finds index of product with given ID. Returns -1 if not found. */
int findByID(int id)
{
    for (int i = 0; i < productCount; i++)
        if (inventory[i].id == id) return i;
    return -1;
}

/* Prints a separator line. */
void printLine(void)
{
    printf("----------------------------------------------------------\n");
}

/* Prints the column header row for product tables. */
void printHeader(void)
{
    printLine();
    printf("%-6s %-22s %-14s %6s %10s %10s\n",
           "ID", "Name", "Category", "Qty", "Price", "Cost");
    printLine();
}

/* Prints a single product row. */
void printProduct(const Product *p)
{
    printf("%-6d %-22s %-14s %6d %10.2f %10.2f\n",
           p->id, p->name, p->category,
           p->quantity, p->price, p->costPrice);
}

/* ================================================================
 *  OPERATION 1 — Add New Product
 * ================================================================ */
void addProduct(void)
{
    if (productCount >= MAX_PRODUCTS) {
        printf("[!] Inventory full. Cannot add more products.\n");
        return;
    }

    Product p;

    /* Assign a unique auto-incremented ID */
    p.id = nextID++;

    printf("\n--- ADD NEW PRODUCT (ID: %d) ---\n", p.id);

    printf("Product Name    : ");
    readLine(p.name, NAME_LEN);
    if (p.name[0] == '\0') { printf("[!] Name cannot be empty.\n"); nextID--; return; }

    printf("Category        : ");
    readLine(p.category, CAT_LEN);
    if (p.category[0] == '\0') strcpy(p.category, "General");

    printf("Quantity        : ");
    if (scanf("%d", &p.quantity) != 1 || p.quantity < 0) {
        printf("[!] Invalid quantity.\n"); flushInput(); nextID--; return;
    }
    flushInput();

    printf("Selling Price   : ");
    if (scanf("%lf", &p.price) != 1 || p.price < 0) {
        printf("[!] Invalid price.\n"); flushInput(); nextID--; return;
    }
    flushInput();

    printf("Cost Price      : ");
    if (scanf("%lf", &p.costPrice) != 1 || p.costPrice < 0) {
        printf("[!] Invalid cost price.\n"); flushInput(); nextID--; return;
    }
    flushInput();

    /* Save product into the global array */
    inventory[productCount++] = p;

    printf("[+] Product '%s' added with ID %d.\n", p.name, p.id);
}

/* ================================================================
 *  OPERATION 2 — Display All Products
 * ================================================================ */
void displayAll(void)
{
    if (productCount == 0) {
        printf("[!] No products in inventory.\n");
        return;
    }

    printf("\n=== ALL PRODUCTS (%d) ===\n", productCount);
    printHeader();
    for (int i = 0; i < productCount; i++)
        printProduct(&inventory[i]);
    printLine();
}

/* ================================================================
 *  OPERATION 3 — Search Product (by ID or Name)
 * ================================================================ */
void searchProduct(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("\nSearch by: 1.ID  2.Name  : ");
    int opt;
    if (scanf("%d", &opt) != 1) { flushInput(); return; }
    flushInput();

    if (opt == 1) {
        /* ── Search by ID ──────────────────────────────────── */
        printf("Enter Product ID : ");
        int id;
        if (scanf("%d", &id) != 1) { flushInput(); return; }
        flushInput();

        int idx = findByID(id);
        if (idx == -1) {
            printf("[-] No product with ID %d.\n", id);
        } else {
            printf("\n--- PRODUCT FOUND ---\n");
            printHeader();
            printProduct(&inventory[idx]);
            printLine();
        }
    }
    else if (opt == 2) {
        /* ── Search by Name (partial, case-insensitive) ─────── */
        char keyword[NAME_LEN];
        printf("Enter name keyword : ");
        readLine(keyword, NAME_LEN);

        int found = 0;
        printf("\n--- SEARCH RESULTS for \"%s\" ---\n", keyword);
        printHeader();
        for (int i = 0; i < productCount; i++) {
            if (containsStr(inventory[i].name, keyword) ||
                containsStr(inventory[i].category, keyword)) {
                printProduct(&inventory[i]);
                found++;
            }
        }
        printLine();
        if (!found) printf("[-] No matches found.\n");
        else        printf("[+] %d match(es) found.\n", found);
    }
    else {
        printf("[!] Invalid option.\n");
    }
}

/* ================================================================
 *  OPERATION 4 — Update Product Details
 * ================================================================ */
void updateProduct(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("Enter Product ID to update : ");
    int id;
    if (scanf("%d", &id) != 1) { flushInput(); return; }
    flushInput();

    int idx = findByID(id);
    if (idx == -1) { printf("[-] Product ID %d not found.\n", id); return; }

    Product *p = &inventory[idx];
    printf("\nCurrent details:\n");
    printHeader();
    printProduct(p);
    printLine();

    /* For each field, pressing Enter keeps the old value. */
    printf("\nEnter new values (press Enter to keep current):\n");

    char buf[NAME_LEN];

    printf("New Name [%s] : ", p->name);
    readLine(buf, NAME_LEN);
    if (buf[0] != '\0') strcpy(p->name, buf);

    printf("New Category [%s] : ", p->category);
    readLine(buf, CAT_LEN);
    if (buf[0] != '\0') strcpy(p->category, buf);

    printf("New Selling Price [%.2f] : ", p->price);
    readLine(buf, NAME_LEN);
    if (buf[0] != '\0') p->price = atof(buf);

    printf("New Cost Price [%.2f] : ", p->costPrice);
    readLine(buf, NAME_LEN);
    if (buf[0] != '\0') p->costPrice = atof(buf);

    printf("[+] Product ID %d updated successfully.\n", id);
    printHeader();
    printProduct(p);
    printLine();
}

/* ================================================================
 *  OPERATION 5 — Delete Product
 * ================================================================ */
void deleteProduct(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("Enter Product ID to delete : ");
    int id;
    if (scanf("%d", &id) != 1) { flushInput(); return; }
    flushInput();

    int idx = findByID(id);
    if (idx == -1) { printf("[-] Product ID %d not found.\n", id); return; }

    printf("Are you sure you want to delete '%s'? (y/n) : ",
           inventory[idx].name);
    char confirm;
    scanf(" %c", &confirm);
    flushInput();

    if (confirm != 'y' && confirm != 'Y') {
        printf("[!] Deletion cancelled.\n");
        return;
    }

    /*
     * Remove by shifting all elements after idx one step left.
     * This keeps the array contiguous without gaps.
     */
    for (int i = idx; i < productCount - 1; i++)
        inventory[i] = inventory[i + 1];

    productCount--;
    printf("[+] Product ID %d deleted.\n", id);
}

/* ================================================================
 *  OPERATION 6 — Update Stock (Restock / Sell)
 * ================================================================ */
void updateStock(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("Enter Product ID : ");
    int id;
    if (scanf("%d", &id) != 1) { flushInput(); return; }
    flushInput();

    int idx = findByID(id);
    if (idx == -1) { printf("[-] Product ID %d not found.\n", id); return; }

    Product *p = &inventory[idx];
    printf("Product : %s  |  Current Stock : %d\n", p->name, p->quantity);
    printf("1. Restock (add stock)\n");
    printf("2. Sell    (reduce stock)\n");
    printf("Choice : ");

    int opt;
    if (scanf("%d", &opt) != 1) { flushInput(); return; }
    flushInput();

    printf("Enter quantity : ");
    int qty;
    if (scanf("%d", &qty) != 1 || qty <= 0) {
        printf("[!] Invalid quantity.\n"); flushInput(); return;
    }
    flushInput();

    if (opt == 1) {
        /* Add stock */
        p->quantity += qty;
        printf("[+] Restocked. New quantity of '%s' : %d\n", p->name, p->quantity);
    }
    else if (opt == 2) {
        /* Reduce stock — cannot go below 0 */
        if (qty > p->quantity) {
            printf("[!] Cannot sell %d units. Only %d in stock.\n",
                   qty, p->quantity);
            return;
        }
        p->quantity -= qty;
        double revenue = qty * p->price;
        double profit  = qty * (p->price - p->costPrice);
        printf("[+] Sold %d unit(s) of '%s'.\n", qty, p->name);
        printf("    Revenue : %.2f  |  Profit : %.2f\n", revenue, profit);
        printf("    Remaining stock : %d\n", p->quantity);

        /* Warn immediately if stock just dropped low */
        if (p->quantity < LOW_STOCK_THRESH)
            printf("[ALERT] Low stock! Only %d unit(s) left.\n", p->quantity);
    }
    else {
        printf("[!] Invalid option.\n");
    }
}

/* ================================================================
 *  OPERATION 7 — Low Stock Alerts
 * ================================================================ */
void lowStockAlert(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("\n=== LOW STOCK ALERT (Quantity < %d) ===\n", LOW_STOCK_THRESH);
    printHeader();

    int found = 0;
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].quantity < LOW_STOCK_THRESH) {
            printProduct(&inventory[i]);
            found++;
        }
    }
    printLine();

    if (found == 0)
        printf("[+] All products have sufficient stock.\n");
    else
        printf("[!] %d product(s) need restocking.\n", found);
}

/* ================================================================
 *  OPERATION 8 — Sort Products
 *  Uses Bubble Sort (easy to follow; fine for ≤200 items)
 * ================================================================ */
void sortProducts(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    printf("Sort by: 1.Name  2.Price (asc)  3.Quantity (asc) : ");
    int opt;
    if (scanf("%d", &opt) != 1) { flushInput(); return; }
    flushInput();

    /* Bubble sort — swap adjacent items if they are in wrong order */
    for (int i = 0; i < productCount - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < productCount - i - 1; j++) {
            int doSwap = 0;

            if      (opt == 1) doSwap = strcmp(inventory[j].name,
                                               inventory[j+1].name) > 0;
            else if (opt == 2) doSwap = inventory[j].price    > inventory[j+1].price;
            else if (opt == 3) doSwap = inventory[j].quantity > inventory[j+1].quantity;

            if (doSwap) {
                Product tmp    = inventory[j];
                inventory[j]   = inventory[j+1];
                inventory[j+1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;   /* Early exit if already sorted */
    }

    printf("[+] Sorted successfully.\n");
    displayAll();
}

/* ================================================================
 *  OPERATION 9 — Category-wise Summary
 * ================================================================ */
void categorySummary(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    /*
     * Collect unique categories on the fly.
     * For each unique category, count products and total qty.
     */
    char  cats[MAX_PRODUCTS][CAT_LEN];
    int   catCount   = 0;
    int   catQty[MAX_PRODUCTS]     = {0};
    int   catItems[MAX_PRODUCTS]   = {0};
    double catValue[MAX_PRODUCTS]  = {0.0};

    for (int i = 0; i < productCount; i++) {
        /* Check if this category was seen before */
        int found = -1;
        for (int c = 0; c < catCount; c++) {
            if (strcmp(inventory[i].category, cats[c]) == 0) {
                found = c;
                break;
            }
        }

        if (found == -1) {
            /* New category — register it */
            strcpy(cats[catCount], inventory[i].category);
            found = catCount++;
        }

        catItems[found]++;
        catQty  [found] += inventory[i].quantity;
        catValue[found] += inventory[i].quantity * inventory[i].price;
    }

    printf("\n=== CATEGORY-WISE SUMMARY ===\n");
    printf("%-20s %8s %10s %15s\n",
           "Category", "Products", "Total Qty", "Total Value");
    printLine();
    for (int c = 0; c < catCount; c++) {
        printf("%-20s %8d %10d %15.2f\n",
               cats[c], catItems[c], catQty[c], catValue[c]);
    }
    printLine();
    printf("Total categories : %d\n", catCount);
}

/* ================================================================
 *  OPERATION 10 — Inventory Report
 * ================================================================ */
void inventoryReport(void)
{
    if (productCount == 0) { printf("[!] Inventory is empty.\n"); return; }

    double totalValue    = 0.0;  /* Sum of (qty × selling price)   */
    double totalCost     = 0.0;  /* Sum of (qty × cost price)      */
    int    totalUnits    = 0;    /* Total units across all products */
    int    lowStockCount = 0;    /* Products below threshold        */
    int    outOfStock    = 0;    /* Products with qty = 0           */
    double mostExpPrice  = 0.0;
    char   mostExpName[NAME_LEN] = "";

    for (int i = 0; i < productCount; i++) {
        Product *p = &inventory[i];
        totalValue += p->quantity * p->price;
        totalCost  += p->quantity * p->costPrice;
        totalUnits += p->quantity;

        if (p->quantity == 0)              outOfStock++;
        if (p->quantity < LOW_STOCK_THRESH) lowStockCount++;
        if (p->price > mostExpPrice) {
            mostExpPrice = p->price;
            strcpy(mostExpName, p->name);
        }
    }

    printf("\n========== INVENTORY REPORT ==========\n");
    printf("  Total Products      : %d\n",     productCount);
    printf("  Total Units         : %d\n",     totalUnits);
    printf("  Inventory Value     : %.2f\n",   totalValue);
    printf("  Total Cost Value    : %.2f\n",   totalCost);
    printf("  Potential Profit    : %.2f\n",   totalValue - totalCost);
    printf("  Low Stock Items     : %d\n",     lowStockCount);
    printf("  Out of Stock Items  : %d\n",     outOfStock);
    printf("  Most Expensive Item : %s (%.2f)\n", mostExpName, mostExpPrice);
    printf("======================================\n");
}

/* ================================================================
 *  OPERATION 11 — Save to File
 *  Uses a simple CSV-like text format so you can open it in Excel.
 * ================================================================ */
void saveToFile(void)
{
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("[!] Cannot open file '%s' for writing.\n", DATA_FILE);
        return;
    }

    /* Write header line */
    fprintf(fp, "ID,Name,Category,Quantity,Price,CostPrice\n");

    /* Write each product as a CSV row */
    for (int i = 0; i < productCount; i++) {
        Product *p = &inventory[i];
        fprintf(fp, "%d,%s,%s,%d,%.2f,%.2f\n",
                p->id, p->name, p->category,
                p->quantity, p->price, p->costPrice);
    }

    /* Also save the next available ID so it continues from the right value */
    fprintf(fp, "#NEXTID,%d\n", nextID);

    fclose(fp);
    printf("[+] Inventory saved to '%s' (%d products).\n",
           DATA_FILE, productCount);
}

/* ================================================================
 *  OPERATION 12 — Load from File
 * ================================================================ */
void loadFromFile(void)
{
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("[!] File '%s' not found. Starting with empty inventory.\n",
               DATA_FILE);
        return;
    }

    productCount = 0;
    char line[256];

    /* Skip the header line */
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        /* Skip comment / metadata lines */
        if (line[0] == '#') {
            /* Parse the saved nextID value */
            int savedID;
            if (sscanf(line, "#NEXTID,%d", &savedID) == 1)
                nextID = savedID;
            continue;
        }

        if (productCount >= MAX_PRODUCTS) break;

        Product p;
        /*
         * sscanf parses the CSV line into the Product struct fields.
         * %[^,] reads everything until the next comma.
         */
        if (sscanf(line, "%d,%49[^,],%29[^,],%d,%lf,%lf",
                   &p.id, p.name, p.category,
                   &p.quantity, &p.price, &p.costPrice) == 6) {
            inventory[productCount++] = p;
        }
    }

    fclose(fp);
    printf("[+] Loaded %d product(s) from '%s'.\n", productCount, DATA_FILE);
}

/* ================================================================
 *  MENU DISPLAY
 * ================================================================ */
void printMenu(void)
{
    printf("\n==========================================\n");
    printf("       INVENTORY MANAGEMENT SYSTEM        \n");
    printf("==========================================\n");
    printf("  1.  Add New Product\n");
    printf("  2.  Display All Products\n");
    printf("  3.  Search Product\n");
    printf("  4.  Update Product Details\n");
    printf("  5.  Delete Product\n");
    printf("  6.  Update Stock (Restock / Sell)\n");
    printf("  7.  Low Stock Alerts\n");
    printf("  8.  Sort Products\n");
    printf("  9.  Category-wise Summary\n");
    printf(" 10.  Inventory Report\n");
    printf(" 11.  Save to File\n");
    printf(" 12.  Load from File\n");
    printf(" 13.  Exit\n");
    printf("==========================================\n");
    printf(" Products in inventory : %d\n", productCount);
    printf("==========================================\n");
}

/* ================================================================
 *  MAIN
 * ================================================================ */
int main(void)
{
    int choice;

    printf("\n******************************************\n");
    printf("*    INVENTORY MANAGEMENT SYSTEM  v1.0  *\n");
    printf("******************************************\n");

    /* Auto-load saved data on startup */
    printf("\n[*] Checking for saved inventory...\n");
    loadFromFile();

    do {
        printMenu();
        printf("Enter your choice (1-13): ");

        /*
         * Guard against non-integer input:
         * If scanf fails (e.g. user types a letter),
         * clear the bad character and restart the loop.
         */
        if (scanf("%d", &choice) != 1) {
            flushInput();
            printf("[!] Please enter a number between 1 and 13.\n");
            choice = 0;
            continue;
        }
        flushInput();   /* Remove the trailing '\n' after the number */

        printf("\n");

        switch (choice)
        {
            case  1: addProduct();      break;
            case  2: displayAll();      break;
            case  3: searchProduct();   break;
            case  4: updateProduct();   break;
            case  5: deleteProduct();   break;
            case  6: updateStock();     break;
            case  7: lowStockAlert();   break;
            case  8: sortProducts();    break;
            case  9: categorySummary(); break;
            case 10: inventoryReport(); break;
            case 11: saveToFile();      break;
            case 12: loadFromFile();    break;
            case 13:
                /* Auto-save on exit */
                printf("[*] Saving inventory before exit...\n");
                saveToFile();
                printf("Goodbye!\n");
                break;
            default:
                printf("[!] Invalid choice. Enter 1 to 13.\n");
        }

    } while (choice != 13);

    return 0;
}