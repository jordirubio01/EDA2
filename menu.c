#include "menu.h"

/**
* Pre: -
* Post: El menú inicial ha sido imprimido por pantalla
*/
void show_first_menu(){ //El menú que aparece nada más entrar a la red social
    printf("%s\n1.\tIniciar sesi%cn\n2.\tRegistrarse\n3.\tListar usuarios\n4.\tListar palabras m%cs frecuentes en la red social\n5.\tSalir\n%s\n", BARS, 162, 160, BARS);
}

/**
 * Pre: -
 * Post: El menú completo ha sido imprimido por pantalla
 */
void show_full_menu(){
    printf("%s\n1.\tEnviar solicitud de amistad\n2.\tGestionar amigos/as\n3.\tHacer una publicaci%cn\n4.\tVer todas las publicaciones\n5.\tVer publicaciones de un usuario\n6.\tCerrar sesi%cn\n%s\n", BARS, 162, 162, BARS);
}


/**
 *
 * @param op
 * @param f
 *
 * Pre: Recibe una opción válida y una dirección de archivo
 * Post: Se ha realizado la opción correcta
 *
 */
void load_option(int op, UserLinked* l_users, Request* l_requests, ActivityLinked* activities, Stack* stack){ // Opciones iniciales (inicio y registro)
    User* logged_user;
    Dictionary* dict = init_dictionary(SIZE_DICT);
    clock_t start, end;
    double total_time, total_sec;
    int total_min;

    if (op == 1){       // Iniciar sesión
        int logged_option;
        logged_user = login(l_users);
        if (logged_user != NULL){
            // Guardamos el tiempo de ejecución actual en el stack
            start = clock();
            push(stack, start);
            // Mostramos el menú de opciones de usuario
            show_full_menu();
            scanf("%d", &logged_option);
            while (logged_option != 6){
                load_user_option(logged_option, l_users, logged_user, l_requests, activities);
                show_full_menu();
                scanf("%d", &logged_option);
            }
            // Recuperamos el tiempo inicial del stack y calculamos el total
            end = clock();
            start = top(stack);
            pop(stack);
            total_time = ((double)(end-start) / CLOCKS_PER_SEC);
            total_min = (int)(total_time) / 60;
            total_sec = total_time - (double) total_min * 60;
            printf("Has cerrado sesi%cn correctamente, %s.\nEstuviste conectado/a durante %d min %.2lf segundos.\n", 162, logged_user->name, total_min, total_sec);
        }
    }
    else if (op == 2){  // Registrar usuario
        fill_profile(l_users);
    }
    else if (op == 3){  // Listar usuarios
        show_users(l_users);
    }
    else if (op == 4){ // Dictionary
        counter_of_words(dict);
        //imprimir 10 palabras
    }
    else printf("Por favor, introduce un n%cmero del 1 al 4.\n", 163);
}

/**
 *
 * @param op
 * @param f_name
 *
 * Pre: Recibe un entero y una dirección de archivo
 * Post: Se ha ejecutado la opción escogida
 */
// ESTA FUNCIÓN LA IMPLEMENTAREMOS EN load_option UNA VEZ SE HAYA INICIADO SESIÓN
void load_user_option(int op, UserLinked* l_users, User* current_user, Request* l_requests, ActivityLinked* activities){ // Opciones de usuario (ya ha iniciado sesión)
    // Enviar solicitud de amistad
    if (op == 1){
        char asked_user[MAX_LENGTH];
        printf("%cA qui%cn quieres agregar? Introduce su nombre de usuario:\n", 168, 130);
        scanf("%s", asked_user);
        if (strcmp(asked_user, current_user->username) == 0) printf("%cNo puedes agregarte a ti mismo!\n", 173);
        if (l_requests == NULL) l_requests = make_request(asked_user, current_user->username, l_requests, l_users);
        else make_request(asked_user, current_user->username, l_requests, l_users);
        save_requests(l_requests);
    }
    // Gestionar solicitudes de amistad
    else if (op == 2){
        int friend_op;
        printf("%s\n1.\tVer lista de amigos/as\n2.\tAceptar o rechazar solicitudes\n%s\n", BARS, BARS);
        scanf("%d", &friend_op);
        if (friend_op == 1) view_friends(current_user);
        else if (friend_op == 2) view_requests(current_user, l_users, l_requests);
    }
    // Realizar publicación
    else if (op == 3){
        new_content(activities, current_user, l_users);
        printf("\nPublicaci%cn realizada con %cxito\n", 162, 130);
    }
    // Gestionar publicaciones
    else if (op == 4){
        print_all_publications(activities);
    }
    // Ver publicaciones de un usuario
    else if (op == 5){
        printf("Escribe el usuario de quien quieres ver sus publicaciones:\n");
        char username[MAX_LENGTH];
        scanf("%s", username);
        UserLinked* x_user = search_user(username, l_users);
        if (x_user == NULL) printf("El usuario %s no existe.\n", username);
        else print_all_publications(x_user->user->content);
    }
}

/******** FUNCIONES STACK ********/
Stack* init_stack(){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = 0;
    return stack;
}

int isEmpty(Stack* stack){
    return (stack->top == 0);
}

int isFull(Stack* stack){
    return (stack->top == MAX_SIZE);
}

Stack* push(Stack* stack, int element){
    if (isFull(stack)){
        printf("El stack est%c lleno, no se puede insertar ning%cn elemento\n", 160, 163);
    }
    else{
        stack->top++;
        stack->data[stack->top] = element;
    }
    return stack;
}

Stack* pop(Stack* stack){
    if (isEmpty(stack)){
        printf("El stack est%c vac%co, no se puede eliminar ning%cn elemento", 160, 161, 163);
    }
    else{
        stack->top--;
    }
    return stack;
}

int top(Stack* stack){
    if (isEmpty(stack)){
        printf("El stack est%c vac%co, no se puede devolver ning%cn elemento", 160, 161, 163);
    }
    else{
        return stack->data[stack->top];
    }
}