#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define FALSE -1
#define TRUE 1

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/

int valid_username(int username){
    FILE* f_username = fopen("EDA 2/usernames.txt", "r");
    char current_username[MAX_LENGHT];
    int state_password = fscanf(f_username,"%s", current_username);
    while (state_password > 0){
        if (strcmp(&username, current_username) == 0){
            return FALSE;
        }
        state_password = fscanf(f_username,"%s", current_username);
    }
    return TRUE;
}


int fill_profile(User* user, FILE* f_user){
    char name[MAX_LENGHT], lastname[MAX_LENGHT], username[MAX_LENGHT];
    char email[MAIL_LENGHT], location[MAX_LENGHT]; int birth_date;
    printf("Introduce tu nombre:\n");
    scanf("%s", name);
    printf("Introduce tu apellido:\n");
    scanf("%s", lastname);
    printf("Fecha de nacimiento [dd/mm/aaaa]:\n");
    scanf("%d", &birth_date);
    printf("Email:\n");
    scanf("%s", email);
    printf("Ciudad:\n");
    scanf("%s", location);

    //GUARDEM LES DADES DEMANADES
    strcmp(user->name, name);
    strcmp(user->lastname, name);
    strcmp(user->email, email);
    strcmp(user->location, location);
    user->birth_date = birth_date;

    printf("Datos introducidos correctamente. Bienvenido/a, %s.\n", user->name);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s, ahora debes elegir un nombre de usuario y una contraseña.\n", user->name);
    printf("Usuario:\n");
    scanf("%s", user->username);
    strcpy(user->username, username);
    if (valid_username(user->username) == FALSE){

    }
}