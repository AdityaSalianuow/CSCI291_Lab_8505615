//all relevant libraries used//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//all #define statements//
#define ESPRESSO 1
#define CAPPUCCINO 2
#define MOCHA 3
#define EXIT 4
#define ADMIN_MODE 5

#define INITIAL_COFFEE_BEANS 50
#define INITIAL_WATER_ML 200
#define INITIAL_MILK_ML 150
#define INITIAL_SYRUP_ML 50

#define COFFEE_BEANS 8

#define WATER_ML_ESPRESSO 30
#define WATER_ML_CAPPUCCINO 30
#define WATER_ML_MOCHA 39

#define MILK_ML_CAPPUCCINO 70
#define MILK_ML_MOCHA 160

#define CHOCOLATE_SYRUP_ML_MOCHA 30

#define DEFAULT_PRICE_ESPRESSO 3.5
#define DEFAULT_PRICE_CAPPUCCINO 4.5
#define DEFAULT_PRICE_MOCHA 5.5

//variables used in the code below//
int current_coffee_beans = INITIAL_COFFEE_BEANS;
int current_water_ml = INITIAL_WATER_ML;
int current_milk_ml = INITIAL_MILK_ML;
int current_chocolate_syrup_ml = INITIAL_SYRUP_ML;
double total_earnings = 0.0;
double price_espresso = DEFAULT_PRICE_ESPRESSO;
double price_cappuccino = DEFAULT_PRICE_CAPPUCCINO;
double price_mocha = DEFAULT_PRICE_MOCHA;

//function prototypes//
bool check_ingredients(int coffee_type);
bool process_payment(double price);
void admin_mode();
void replenish_ingredients();
void change_coffee_prices();
void collect_earnings();
void display_earnings_and_ingredients();
int coffee_selection();

//main function//
int main() 
{
    int main_menu_choice;

    //while loop for the main menu//
    while (1) 
    {
        printf("\nMain Menu:\n");
        printf("1. Order a coffee type\n");
        printf("2. Admin mode for the coffee maker operator\n");
        printf("3. End the application execution\n");
        printf("Choose an option: ");
        scanf("%d", &main_menu_choice);

        //switch for the 3 options and a default for invalid choice option//
        switch (main_menu_choice) 
        {
            case 1:
                coffee_selection();
                break;
            case 2:
                admin_mode();
                break;
            case 3:
                printf("Thank you for using the coffee machine!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

//defined coffee selection function//
int coffee_selection() 
{
    int customer_button;
    char confirm;

    //printf statements displaying the options, scanf statement to read the user's input//
    printf("\nChoose a coffee\n");
    printf("Enter 1 for Espresso     %.1f AED\n", price_espresso);
    printf("Enter 2 for Cappuccino   %.1f AED\n", price_cappuccino);
    printf("Enter 3 for Mocha        %.1f AED\n", price_mocha);
    printf("Enter 4 to Exit\n");
    scanf("%d", &customer_button);

    //if statement for if the user prompts the program to exit the coffee selection menu//
    if (customer_button == EXIT) 
    {
        return EXIT;
    }

    //if statement for if the user chooses a number below 1 or above 3 resulting in an error//
    if (customer_button < 1 || customer_button > 3) 
    {
        printf("Invalid selection. Please choose a valid coffee option.\n");
        return 0;
    }

    //print message for confirmation of order and scan the user input//
    printf("Confirm your selection (y/n): ");
    scanf(" %c", &confirm);

    
  /*do while loop in which it prompts the user to confirm their order, it only allows inpupts of 'y' or 'n' as yes or no
  otherwise the program prompts the user whether they'd like to confirm their order again, yes continues the program and
  no takes the user back to the coffee selection*/
    do {
        printf("Confirm your selection (y/n): ");
        scanf(" %c", &confirm);

        if (confirm != 'y' && confirm != 'Y') 
        {
            printf("Invalid input. Would you like to confirm your order again? (y/n): ");
            scanf(" %c", &confirm);
            if (confirm == 'n' || confirm == 'N') 
            {
                printf("Returning to coffee selection...\n\n");
                return 0;
            }
        }
    } while (confirm != 'y' && confirm != 'Y');

    //Assigning value to variable price using ternary conditonal operator ? to set the price of the coffee to the correct price//
    double price = (customer_button == ESPRESSO) ? price_espresso :
                   (customer_button == CAPPUCCINO) ? price_cappuccino :
                   price_mocha;

    /*if and else ifs to check the number of ingredients and whether there is enough of each ingredient using below boolean, prints 
    relevant insuffecient ingredients message if ingredients are not enough*/
    if (check_ingredients(customer_button)) 
    {
        if (customer_button == ESPRESSO) 
        {
            current_coffee_beans -= COFFEE_BEANS;
            current_water_ml -= WATER_ML_ESPRESSO;
        } 
        else if (customer_button == CAPPUCCINO) 
        {
            current_coffee_beans -= COFFEE_BEANS;
            current_water_ml -= WATER_ML_CAPPUCCINO;
            current_milk_ml -= MILK_ML_CAPPUCCINO;
        } 
        else if (customer_button == MOCHA) 
        {
            current_coffee_beans -= COFFEE_BEANS;
            current_water_ml -= WATER_ML_MOCHA;
            current_milk_ml -= MILK_ML_MOCHA;
            current_chocolate_syrup_ml -= CHOCOLATE_SYRUP_ML_MOCHA;
        }
        //if else statement to save the total earnings//
        if (process_payment(price)) 
        {
            total_earnings += price;
            printf("Thank you! Your coffee is being prepared.\n");
        } 
        else 
        {
            printf("Payment unsuccessful. Returning to coffee selection...\n");
        }
    } 
    else 
    {
        printf("Not enough ingredients. Returning to coffee selection...\n");
    }

    return 0;
}

//boolean function using if else statements to check the ingredients//
bool check_ingredients(int coffee_type) 
{
    if (coffee_type == ESPRESSO) 
    {
        return (current_coffee_beans >= COFFEE_BEANS && current_water_ml >= WATER_ML_ESPRESSO);
    } 
    else if (coffee_type == CAPPUCCINO) 
    {
        return (current_coffee_beans >= COFFEE_BEANS &&
                current_water_ml >= WATER_ML_CAPPUCCINO &&
                current_milk_ml >= MILK_ML_CAPPUCCINO);
    } 
    else if (coffee_type == MOCHA) 
    {
        return (current_coffee_beans >= COFFEE_BEANS &&
                current_water_ml >= WATER_ML_MOCHA &&
                current_milk_ml >= MILK_ML_MOCHA &&
                current_chocolate_syrup_ml >= CHOCOLATE_SYRUP_ML_MOCHA);
    }
    return false;
}

//boolean function using while loop with nested if loop for payment of 1.0 and 0.5 AED coins only//
bool process_payment(double price) 
{
    double total_paid = 0.0;
    double coin;

    printf("Enter coins (1.0 or 0.5 AED) to pay %.2f AED:\n", price);

    while (total_paid < price) 
    {
        printf("Enter coin: ");
        scanf("%lf", &coin);

        if (coin == 1.0 || coin == 0.5) 
        {
            total_paid += coin;
            printf("Total paid: %.1f AED\n", total_paid);
        } 
        else 
        {
            printf("Invalid coin. Use 1.0 or 0.5 AED.\n");
        }
    }
    printf("Payment successful!\n");
    return true;
}

//Admin mode function//
void admin_mode() 
{
    int password;
    //Prints and scans for admin password//
    printf("Enter admin password: ");
    scanf("%d", &password);
    //Used if statement to set the password//
    if (password == 1234) 
    {
        //Unlocks admin mode features after password is enterred, calls all other relevant admin mode functions//
        int choice;
        do 
        {
            printf("\nAdmin Menu:\n");
            printf("1. Display earnings and ingredients\n");
            printf("2. Replenish ingredients\n");
            printf("3. Change coffee prices\n");
            printf("4. Exit Admin Mode\n");
            printf("Choose an option: ");
            scanf("%d", &choice);

            if (choice == 1) 
            {
                display_earnings_and_ingredients();
            } 
            else if (choice == 2) 
            {
                replenish_ingredients();
            } 
            else if (choice == 3) 
            {
                change_coffee_prices();
            } 
            else if (choice != 4) 
            {
                printf("Invalid choice. Try again.\n");
            }
        } while (choice != 4);
    } 
    else 
    {
        printf("Incorrect password. Returning to main menu...\n");
    }
}

/*Function uses rand to replenish ingredients a random amount within set bounds, 50 - 100 for coffee beans, 300ml - 500ml for milk
and water, 100ml - 200ml of chocolate syrup*/
void replenish_ingredients() 
{   
    int added_beans = 50 + rand() % 51;
    int added_water = 300 + rand() % 201;
    int added_milk = 300 + rand() % 201;
    int added_syrup = 100 + rand() % 101;

    current_coffee_beans += added_beans;
    current_water_ml += added_water;
    current_milk_ml += added_milk;
    current_chocolate_syrup_ml += added_syrup;

    printf("Ingredients replenished.\n");
    printf("Updated Ingredient Levels:\n");
    printf("Coffee beans: %d g\n", current_coffee_beans);
    printf("Water: %d ml\n", current_water_ml);
    printf("Milk: %d ml\n", current_milk_ml);
    printf("Chocolate syrup: %d ml\n", current_chocolate_syrup_ml);
}

//function to change coffee price for admin, uses basic printf and scanf to save new prices in price variables//
void change_coffee_prices() 
{
    printf("Enter new price for Espresso: ");
    scanf("%lf", &price_espresso);
    printf("Enter new price for Cappuccino: ");
    scanf("%lf", &price_cappuccino);
    printf("Enter new price for Mocha: ");
    scanf("%lf", &price_mocha);
    printf("Prices updated successfully.\n");
}

//function to view earnings and ingredients, uses printf to display//
void display_earnings_and_ingredients() 
{
    printf("\nIngredients:\n");
    printf("Coffee beans: %d g\n", current_coffee_beans);
    printf("Water: %d ml\n", current_water_ml);
    printf("Milk: %d ml\n", current_milk_ml);
    printf("Chocolate syrup: %d ml\n", current_chocolate_syrup_ml);
    printf("Total earnings: %.2f AED\n", total_earnings);

//collection of earnings, printf and scanf used to confirm collection of earnings and then function collect_earnings() is called//
    char collect;
    printf("Collect earnings? (y/n): ");
    scanf(" %c", &collect);

    if (collect == 'y' || collect == 'Y') 
    {
        collect_earnings();
    }
}

//function to collect earnings, print relevant message and reset total earnings to 0//
void collect_earnings() 
{
    printf("Collected %.1f AED\nResetting earnings to 0\nRemember to collect earnings\n", total_earnings);
    total_earnings = 0.0;
}
