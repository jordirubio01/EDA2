#include "menu.h"

int main() {
    // Recuperamos los usuarios registrados hasta ahora
    UserLinked* l_users = init_list();
    init_friends(l_users);
    Request* l_requests = init_queue(l_users);
    ActivityLinked* activities = init_activity_list(l_users);
    Stack* stack = init_stack();

    // Empieza el programa (inicio/registro/listar usuarios)
    printf("%s\n\t\t\t\t\t   %c %c Culture Lovers %c %c\n", BARS, 3, 5, 5, 3);
    int option, total_min;
    clock_t start, end;
    double total_time, total_sec;
    // Guardamos el tiempo de ejecución actual en el stack
    start = clock();
    push(stack, start);

    // Mostramos el menú
    show_first_menu();
    scanf("%d", &option);
    while (option != 5){
        load_option(option, l_users, l_requests, activities, stack);
        show_first_menu();
        scanf("%d", &option);
    }
    // Recuperamos el tiempo inicial del stack y calculamos el total
    end = clock();
    start = top(stack);
    pop(stack);
    total_time = ((double)(end-start) / CLOCKS_PER_SEC);
    total_min = (int)(total_time) / 60;
    total_sec = total_time - (double) total_min * 60;

    // Mensaje final
    printf("El programa ha estado activo durante %d min %.2lf segundos.\n%cHasta la pr%cxima!", total_min, total_sec, 173, 162);
    return 0;
}
