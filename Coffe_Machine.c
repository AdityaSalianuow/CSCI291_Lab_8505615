# include <stdio.h>
# include <math.h>

int coffee_selection(int customer_button,int espresso, int cappuccino, int mocha);

int main()
{
    int customer_button;
    int espresso;
    int cappuccino;
    int mocha;

    espresso = 1;
    cappuccino = 2;
    mocha = 3;

    printf("Choose a coffee - Enter 1 for Espresso, Enter 2 for Cappuccino, Enter 3 for Mocha ");
    scanf("%d",&customer_button);
    coffee_selection(customer_button, espresso, cappuccino, mocha);
    return 0;
}

int coffee_selection(int customer_button, int espresso, int cappuccino, int mocha)
{
    if (customer_button == espresso)
        printf("Brewing Espresso\n");
    else if (customer_button == cappuccino)
        printf("Brewing Cappucino\n");
    else if (customer_button == mocha)
        printf("Brewing Mocha\n");
    else
        printf("Invalid selection. Please choose a valid coffee option.\n");
}
