#include <stdio.h>
#include "menu.h"
#include "user.h"

/**
* Pre: -
* Post: El menú inicial ha sido imprimido por pantalla
*/
void show_first_menu(){ //El menú que aparece nada más entrar a la red social
    printf("1.\tInicio\n2.\tRegistrarse\n3.\tListar usuarios\n4.\tSalir\n");
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
 * Pre: Recibe una opción válida y un archivo
 * Post: Se ha realizado la opción correcta
 *
 */
void load_option(int op, FILE* f){ // Opciones iniciales (inicio y registro)
    User* user;
    if (op == 1){       // Iniciar sesión
        // FUNCIÓN
    }
    else if (op == 2){  // Registrar usuario
        FILE* f_user = fopen("EDA 2/users.txt", "w");
        user = fill_profile(f_user);

        // Añadiremos el usuario al fichero
        /*if (user != NULL){
            save_user(f, user);
        }*/
    }
    else if (op == 3){  // Listar usuarios
        // FUNCIÓN
    }
}

/**
 *
 * @param op
 */

// ESTA FUNCIÓN LA IMPLEMENTAREMOS EN load_option UNA VEZ SE HAYA INICIADO SESIÓN
void load_user_option(int op, FILE*){ // Opciones de usuario (ya ha iniciado sesión)
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