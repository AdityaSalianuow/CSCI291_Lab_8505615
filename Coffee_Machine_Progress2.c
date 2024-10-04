#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define ESPRESSO 1
#define CAPPUCCINO 2
#define MOCHA 3
#define EXIT 4

#define COFFEE_BEAN_ESPRESSO 8
#define COFFEE_BEAN_CAPPUCCINO 8
#define COFFEE_BEAN_MOCHA 8

#define WATER_ML_ESPRESSO 30
#define WATER_ML_CAPPUCCINO 30
#define WATER_ML_MOCHA 39

#define MILK_ML_CAPPUCCINO 70
#define MILK_ML_MOCHA 160

#define CHOCOLATE_SYRUP_ML_MOCHA 30

#define PRICE_ESPRESSO 3.5
#define PRICE_CAPPUCCINO 4.5
#define PRICE_MOCHA 5.5

int current_coffee_beans = 50;
int current_water_ml = 200;  
int current_milk_ml = 150;    
int current_chocolate_syrup_ml = 50;  

bool check_ingredients(int coffee_type);
int coffee_selection();
bool process_payment(double price);

int main() 
{
    coffee_selection();
    return 0;
}

int coffee_selection() 
{
    int customer_button;
    char confirm;

    printf("Choose a coffee\nEnter 1 for Espresso     %.1f AED\nEnter 2 for Cappuccino   %.1f AED\nEnter 3 for Mocha        %.1f AED\nEnter 4 to Exit\n", 
           PRICE_ESPRESSO, PRICE_CAPPUCCINO, PRICE_MOCHA);
    scanf("%d", &customer_button);

    if (customer_button == ESPRESSO) {
        printf("You selected Espresso.\n");
    } else if (customer_button == CAPPUCCINO) {
        printf("You selected Cappuccino.\n");
    } else if (customer_button == MOCHA) {
        printf("You selected Mocha.\n");
    } else if (customer_button == EXIT) {
        printf("Exiting the coffee selection.\n");
        return 0;
    } else {
        printf("Invalid selection. Please choose a valid coffee option.\n");
        return coffee_selection();
    }

    printf("Confirm your selection (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'n' || confirm == 'N') {
        printf("Returning to coffee selection...\n\n");
        return coffee_selection();
    } else if (confirm == 'y' || confirm == 'Y') {
        if (check_ingredients(customer_button)) {
            double price;
            if (customer_button == ESPRESSO) {
                current_coffee_beans -= COFFEE_BEAN_ESPRESSO;
                current_water_ml -= WATER_ML_ESPRESSO;
                price = PRICE_ESPRESSO;
            } else if (customer_button == CAPPUCCINO) {
                current_coffee_beans -= COFFEE_BEAN_CAPPUCCINO;
                current_water_ml -= WATER_ML_CAPPUCCINO;
                current_milk_ml -= MILK_ML_CAPPUCCINO;
                price = PRICE_CAPPUCCINO;
            } else if (customer_button == MOCHA) {
                current_coffee_beans -= COFFEE_BEAN_MOCHA;
                current_water_ml -= WATER_ML_MOCHA;
                current_milk_ml -= MILK_ML_MOCHA;
                current_chocolate_syrup_ml -= CHOCOLATE_SYRUP_ML_MOCHA;
                price = PRICE_MOCHA;
            }

            if (process_payment(price)) {
                printf("Thank you! Your coffee is being prepared.\n");
            } else {
                printf("Payment was unsuccessful. Returning to coffee selection...\n\n");
                return coffee_selection();
            }
        } else {
            printf("Not enough ingredients\nReturning to coffee selection...\n\n");
            return coffee_selection();
        }
    } else {
        printf("Invalid confirmation input. Returning to coffee selection.\n\n");
        return coffee_selection();
    }

    return 0;
}

bool check_ingredients(int coffee_type) 
{
    if (coffee_type == ESPRESSO) {
        return (current_coffee_beans >= COFFEE_BEAN_ESPRESSO &&
                current_water_ml >= WATER_ML_ESPRESSO);
    } else if (coffee_type == CAPPUCCINO) {
        return (current_coffee_beans >= COFFEE_BEAN_CAPPUCCINO &&
                current_water_ml >= WATER_ML_CAPPUCCINO &&
                current_milk_ml >= MILK_ML_CAPPUCCINO);
    } else if (coffee_type == MOCHA) {
        return (current_coffee_beans >= COFFEE_BEAN_MOCHA &&
                current_water_ml >= WATER_ML_MOCHA &&
                current_milk_ml >= MILK_ML_MOCHA &&
                current_chocolate_syrup_ml >= CHOCOLATE_SYRUP_ML_MOCHA);
    }
    return false;
}

bool process_payment(double price) {
    double total_paid = 0.0;
    double coin;
    
    printf("Please enter coins (1.0 or 0.5 AED) to pay for your coffee (total price: %.2f AED):\n", price);
    
    while (total_paid < price) {
        printf("Enter coin (1.0 or 0.5 AED): ");
        scanf("%lf", &coin);

        if (coin == 1.0 || coin == 0.5) {
            total_paid += coin;
            printf("Total paid: %.1f AED\n", total_paid);
        } else {
            printf("Invalid coin. Please enter 1.0 or 0.5 AED.\n");
        }

        if (total_paid >= price) {
            printf("Payment successful! Total paid: %.1f AED\n", total_paid);
            return true;
        }
    }

    return false;
}
