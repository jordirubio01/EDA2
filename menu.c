#include <stdio.h>
#include "menu.h"
#include "user.h"

/**
* Pre: -
* Post: El menú ha sido imprimido por pantalla
*/
void show_menu(){
    printf("1.\tInicio\n2.\tRegistrarse\n");
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
 *
 * Pre: Recibe una opción válida
 * Post: Se ha realizado la opción correcta
 */
void load_option(int op, FILE* f){
    if (op == 1) ;
        //PROGRAMA
    else if (op == 2){
        User new;
        FILE* f_user = fopen("EDA 2/users.txt", "w");
        fill_profile(&new, f_user);
    }
}