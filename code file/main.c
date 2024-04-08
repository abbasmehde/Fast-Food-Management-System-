#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

float price_stack[SIZE];
int top = -1;

void insert(int data, char food_name[50], int quantity, float price);
void display();
void main_menu();
void order();
void end();

void placeorder();

struct node {
    char food_name[50];
    float price;
    int quantity;
    int data;
    struct node *next;
};

struct node *head = NULL;

int main() {
    main_menu();
    order();
    return 0;
}

void main_menu() {
    insert(1070, "Burger", 100, 175.87);
    insert(1071, "Pizza", 150, 220.50);
    insert(1072, "Fries", 200, 80.25);
    insert(1073, "Sandwich", 120, 150.00);
    insert(1074, "Salad", 80, 120.75);
    insert(1075, "Pasta", 90, 200.00);
    insert(1076, "Steak", 70, 300.50);
    insert(1077, "Sushi", 50, 250.00);
    insert(1078, "Taco", 110, 180.25);
    insert(1079, "Soup", 130, 90.75);
    display();
}

void order() {
    int userenter;
    while (1) {

        printf("1. Place Order\n");
        printf("2. Cancel Order\n");
        printf("3. Total Price\n");
        printf("4. Exit\n");
        printf("What would you like to do? (1-4): ");
        scanf("%d", &userenter);
        switch (userenter) {
            case 1:
                placeorder();
                break;
            case 2:
                if (top == -1) {
                    printf("\nNo items in the order.\n");
                } else {
                    price_stack[top] = 0;
                    printf("\nYour order has been canceled.\n");
                    end();
                }
                break;
            case 3:
                if (top == -1) {
                    printf("\nNo items in the order.\n");
                } else {
                    float total_price = 0;
                    for (int i = 0; i <= top; i++) {
                        total_price += price_stack[i];
                    }
                    printf("\nTotal price of your order: $%.2f\n", total_price);
                }
                break;
            case 4:
                end();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    }
}

void insert(int data, char food_name[50], int quantity, float price) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = data;
    temp->quantity = quantity;
    temp->price = price;
    strcpy(temp->food_name, food_name);
    temp->next = head;
    head = temp;
}

void display() {
    struct node *ptr;
    ptr = head;
    printf("\n----------------------------------------------------\n");
    printf("| %-10s | %-20s | %-10s | %-10s |\n", "Serial", "Food Name", "Price", "Quantity");
    printf("----------------------------------------------------\n");
    while (ptr != NULL) {
        printf("| %-10d | %-20s | $%-9.2f | %-10d |\n", ptr->data, ptr->food_name, ptr->price, ptr->quantity);
        ptr = ptr->next;
    }
    printf("----------------------------------------------------\n");
}

void placeorder() {
    float total_price = 0, item_price = 0;
    struct node *temp;
    temp = head;
    printf("\nPlease enter the serial number of the item you want to order: ");
    int snumber, quantity;
    scanf("%d", &snumber);
    if (snumber >= 1070 && snumber <= 1080) {
        printf("Please enter the quantity: ");
        scanf("%d", &quantity);
        while (temp != NULL) {
            if (temp->data == snumber) {
                if (temp->quantity < quantity) {
                    printf("\nSorry, the requested quantity is not available.\n");
                    return;
                } else {
                    temp->quantity -= quantity;
                    item_price = temp->price * quantity;
                    total_price += item_price;
                    printf("\nYour order (Serial Number: %d, Price: $%.2f) has been placed.\n", temp->data, total_price);
                    ++top;
                    price_stack[top] = item_price;
                    return;
                }
            }
            temp = temp->next;
        }
        printf("Invalid choice. Please try again.\n");
    } else {printf("Invalid choice. Please try again.\n");}
}

void end() {
    printf("\nThank you for visiting us!\n");
    exit(0);
}
