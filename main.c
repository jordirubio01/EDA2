#include <stdio.h>
#include <stdbool.h>
#include "menu.h"

int main() {
    // Recuperamos los usuarios registrados hasta ahora
    char f_users[MAX_LENGTH] = "resources/users.txt";
    UserLinked* l_users = init_list(f_users);


    // Empieza el programa (inicio/registro/listar usuarios)
    printf("%s\n\t\t\t\t\t   %c %c Culture Lovers %c %c\n%s\n", BARS, 3, 5, 5, 3, BARS);
    int option; char option_user;
    show_first_menu();
    user_option(&option);
    while (option != 4){
        load_option(option, f_users, l_users);
        show_first_menu();
        user_option(&option);
    }
    return 0;
}
