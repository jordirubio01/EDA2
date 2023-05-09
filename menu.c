#include <stdio.h>
#include "menu.h"
#include "user.h"

/**
* Pre: -
* Post: El menú inicial ha sido imprimido por pantalla
*/
void show_first_menu(){
    printf("1.\tInicio\n2.\tRegistrarse\n");
}

/*
 * Pre: -
 * Post: El menú completo ha sido imprimido por pantalla
 */
void show_full_menu(){
    printf("1.\tEnviar solicitud de amistad\n2.\tGestionar solicitudes pendientes\n3.\tPublicar\n4.\tGestionar publicaciones\n");
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
 * @param op, f
 *
 * Pre: Recibe una opción válida y un archivo
 * Post: Se ha realizado la opción correcta
 */
void load_option(int op, FILE* f){
    User* user;
    if (op == 1) ;
        //PROGRAMA
    else if (op == 2){
        User new;
        FILE* f_user = fopen("EDA 2/users.txt", "w");
        user = fill_profile(&new, f_user);
        /*if (user != NULL){
            save_user(f, user);
        }*/
    }
}