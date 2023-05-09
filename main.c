#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include "user.h"

int main() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t BCN Chat \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    int option;
    FILE* f_users = fopen("resources/users.txt", "w");
    show_first_menu();
    user_option(&option);
    while (option != 4){
        load_option(option, f_users);
        user_option(&option);
    }
    return 0;
}
