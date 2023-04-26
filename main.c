#include <stdio.h>
#include "menu.h"
#include "user.h"

int main() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t BCN Chat \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int option;
    show_menu();
    user_option(&option);
    load_option(option);
    return 0;
}
