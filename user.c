#include <stdio.h>
#include <stdbool.h>
#include "user.h"

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
int valid_password()
void read_usernames()
int fill_profile(User* user, FILE* file){
    char name[20], lastname[20], username[20], email[50], location[20]; int birth_date;
    printf("Introduce tu nombre:\n");
    scanf("%s", name);
    printf("Introduce tu apellido:\n");
    scanf("%s", lastname);
    printf("Nombre de usuario:\n");
    scanf("%s", username);
    printf("Fecha de nacimiento [dd/mm/aaaa]:\n");
    scanf("%d", &birth_date);
    printf("Email:\n");
    scanf("%s", email);
    printf("Ciudad:\n");
    scanf("%s", location);
    printf("Datos introducidos correctamente. Bienvenido/a, %s.\n", name);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s, ahora debes elegir un nombre de usuario y una contraseña.\n", name)
    printf("Usuario:\n");
    scan
}