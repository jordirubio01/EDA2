#include <stdio.h>
#include "menu.h"

/**
* Pre: -
* Post: El menú inicial ha sido imprimido por pantalla
*/
void show_first_menu(){ //El menú que aparece nada más entrar a la red social
    printf("%s\n1.\tIniciar sesi%cn\n2.\tRegistrarse\n3.\tListar usuarios\n4.\tSalir\n%s\n", BARS, 162, BARS);
}

/**
 * Pre: -
 * Post: El menú completo ha sido imprimido por pantalla
 */
void show_full_menu(){
    printf("%s\n1.\tEnviar solicitud de amistad\n2.\tGestionar amigos/as\n3.\tPublicar\n4.\tGestionar publicaciones\n5.\tCerrar sesi%cn\n%s\n", BARS, 162, BARS);
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
void load_option(int op, UserLinked* l_users, Request* l_requests){ // Opciones iniciales (inicio y registro)
    User* logged_user;
    if (op == 1){       // Iniciar sesión
        int logged_option;
        logged_user = login(l_users);
        if (logged_user != NULL){
            show_full_menu();
            scanf("%d", &logged_option);
            while (logged_option != 5){
                load_user_option(logged_option, l_users, logged_user, l_requests);
                show_full_menu();
                scanf("%d", &logged_option);
            }
        }
    }
    else if (op == 2){  // Registrar usuario
        fill_profile(l_users);
    }
    else if (op == 3){  // Listar usuarios
        show_users(l_users);
    }
    else printf("Por favor, introduce un n%cmero del 1 al 4\n", 163);
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
void load_user_option(int op, UserLinked* l_users, User* current_user, Request* l_requests){ // Opciones de usuario (ya ha iniciado sesión)
    if (op == 1){       // Enviar solicitud de amistad
        char asked_user[MAX_LENGTH];
        printf("%cA qui%cn quieres agregar? Introduce su nombre de usuario:\n", 168, 130);
        scanf("%s", asked_user);
        if (strcmp(asked_user, current_user->username) == 0) printf("%cNo puedes agregarte a ti mismo!\n", 173);
        if (l_requests == NULL) l_requests = make_request(asked_user, current_user->username, l_requests, l_users);
        else make_request(asked_user, current_user->username, l_requests, l_users);
        save_requests(l_requests);
    }
    else if (op == 2){  // Gestionar solicitudes de amistad
        int friend_op;
        printf("%s\n1.\tVer lista de amigos/as\n2.\tAceptar o rechazar solicitudes\n%s\n", BARS, BARS);
        scanf("%d", &friend_op);
        if (friend_op == 1) view_friends(current_user);
        else if (friend_op == 2) view_requests(current_user, l_users, l_requests);
    }
    else if (op == 3){  // Realizar publicación
        // FUNCIÓN
    }
    else if (op == 4){  // Gestionar publicaciones
        // FUNCIÓN
    }
}