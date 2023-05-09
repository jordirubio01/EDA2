#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "user.h"

int main() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t BCN Chat \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int option;
    FILE* f_users = fopen("users.txt", "w");
    show_first_menu();
    user_option(&option);
    load_option(option, f_users);
    return 0;
}
