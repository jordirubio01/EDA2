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

int valid_username(char username[MAX_LENGTH]){
    FILE* f_username = fopen("EDA 2/usernames.txt", "r");
    char current_username[MAX_LENGTH];
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
    char name[MAX_LENGTH], lastname[MAX_LENGTH], username[MAX_LENGTH];
    char email[MAIL_LENGTH], location[MAX_LENGTH];
    int birth_date;
    printf("Introduce tu nombre:\n");
    scanf("%s", name);
    printf("Introduce tu apellido:\n");
    scanf("%s", lastname);
    printf("Fecha de nacimiento [ddmmaaaa]:\n");
    scanf("%d", &birth_date);
    printf("Email:\n");
    scanf("%s", email);
    printf("Ciudad:\n");
    scanf("%s", location);

    //GUARDEM LES DADES DEMANADES
    strcpy(user->name, name);
    strcpy(user->lastname, name);
    strcpy(user->email, email);
    strcpy(user->location, location);
    user->birth_date = birth_date;

    printf("Datos introducidos correctamente. Bienvenido/a, %s.\n", user->name);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s, ahora debes elegir un nombre de usuario y un password.\n", user->name);
    printf("Usuario:\n");
    scanf("%s", user->username);
    strcpy(user->username, username);
    while (valid_username(user->username) == FALSE){
        printf("El nombre de usuario introducido no está disponible. Introduzca otro:\n");
        scanf("%s", user->username);
        strcpy(user->username, username);
    }
    //Tenemos que comprobar que la contraseña sea válida (igual que el nombre de usuario)
    printf("Password:\n");
    scanf("%s", user->username);
    return 0;
}