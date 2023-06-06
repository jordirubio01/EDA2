#include "menu.h"

int main() {
    // Recuperamos los usuarios registrados hasta ahora
    UserLinked* l_users = init_list();
    init_friends(l_users);
    Request* l_requests = init_queue(l_users);

    // Empieza el programa (inicio/registro/listar usuarios)
    printf("%s\n\t\t\t\t\t   %c %c Culture Lovers %c %c\n", BARS, 3, 5, 5, 3);
    int option;
    show_first_menu();
    scanf("%d", &option);
    while (option != 4){
        load_option(option, l_users, l_requests);
        show_first_menu();
        scanf("%d", &option);
    }
    printf("%cHasta la pr%cxima!", 173, 162);
    return 0;
}
