#include <stdio.h>
#include "menu.h"

/**
* Pre: -
* Post: El menú inicial ha sido imprimido por pantalla
*/
void show_first_menu(){ //El menú que aparece nada más entrar a la red social
    printf("1.\tIniciar sesi%cn\n2.\tRegistrarse\n3.\tListar usuarios\n4.\tSalir\n%s\n", 162, BARS);
}

/**
 * Pre: -
 * Post: El menú completo ha sido imprimido por pantalla
 */
void show_full_menu(){
    printf("1.\tEnviar solicitud de amistad\n2.\tGestionar solicitudes pendientes\n3.\tPublicar\n4.\tGestionar publicaciones\n5.\tSalir\n");
}

/**
 *
 * @param op
 *
 * Pre: Recibe un entero positivo
 * Post: -
 *
 */
void user_option(int* op){
    scanf("%d", op);
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
void load_option(int op, char f_name[MAX_LENGTH], UserLinked* l_users){ // Opciones iniciales (inicio y registro)
    User* logged_user;
    if (op == 1){       // Iniciar sesión
        logged_user = login(l_users);
    }
    else if (op == 2){  // Registrar usuario
        fill_profile(f_name, l_users);

        // Añadiremos el usuario al fichero
        /*if (user != NULL){
            save_user(f, user);
        }*/
    }
    else if (op == 3) {  // Listar usuarios
        show_users(l_users);
    }
    else if (op == 4)
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
void load_user_option(int op, char f_name[MAX_LENGTH], UserLinked* l_users){ // Opciones de usuario (ya ha iniciado sesión)
    if (op == 1){       // Enviar solicitud de amistad
        // FUNCIÓN
    }
    else if (op == 2){  // Gestionar solicitudes de amistad
        // FUNCIÓN
    }
    else if (op == 3){  // Realizar publicación
        // FUNCIÓN
    }
    else if (op == 4){  // Gestionar publicaciones
        // FUNCIÓN
    }
}