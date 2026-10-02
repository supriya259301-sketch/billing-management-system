#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    char name[30];
    int quantity;
    float price;
    float total;
};

void addBill();
void viewBills();
void searchBill();

int main() {
    int choice;
    while (1) {
        printf("\n--- Billing System ---\n");
        printf("1. Add New Bill\n");
        printf("2. View All Bills\n");
        printf("3. Search Bill by Customer Name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addBill(); break;
            case 2: viewBills(); break;
            case 3: searchBill(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addBill() {
    FILE *fp;
    struct item items[50];
    int n, i;
    float total = 0;
    char customer[50];
    
    fp = fopen("bills.txt", "a");
    printf("\nEnter Customer Name: ");
    scanf("%s", customer);
    printf("Enter Number of Items: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter Item %d Name: ", i + 1);
        scanf("%s", items[i].name);
        printf("Enter Quantity: ");
        scanf("%d", &items[i].quantity);
        printf("Enter Price per Item: ");
        scanf("%f", &items[i].price);
        items[i].total = items[i].quantity * items[i].price;
        total += items[i].total;
    }

    fprintf(fp, "\nCustomer: %s\n", customer);
    fprintf(fp, "-----------------------------------\n");
    fprintf(fp, "Item\tQty\tPrice\tTotal\n");
    for (i = 0; i < n; i++) {
        fprintf(fp, "%s\t%d\t%.2f\t%.2f\n", items[i].name, items[i].quantity, items[i].price, items[i].total);
    }
    fprintf(fp, "-----------------------------------\n");
    fprintf(fp, "Total Bill: %.2f\n\n", total);
    fclose(fp);

    printf("\nBill generated successfully!\nTotal Amount: %.2f\n", total);
}

void viewBills() {
    FILE *fp;
    char ch;
    fp = fopen("bills.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }
    printf("\n--- All Bills ---\n\n");
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

void searchBill() {
    FILE *fp;
    char line[200], name[50];
    int found = 0;
    printf("\nEnter Customer Name to Search: ");
    scanf("%s", name);
    fp = fopen("bills.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, name)) {
            printf("\nBill Found:\n");
            printf("%s", line);
            found = 1;
        }
    }
    fclose(fp);
    if (!found)
        printf("Bill not found!\n");
}