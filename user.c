#include <stdio.h>
#include "user.h"

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
int fill_profile(User* user){
    char name[20], username[20], email[50], location[20]; int birth_date;
    printf("Introduce tu nombre real:\n");
    scanf("%s", name);
    printf("Nombre de usuario:\n");
    scanf("%s", username);
    printf("Edad:\n");
    scanf("%d", &birth_date);
    printf("Email:\n");
    scanf("%s", email);
    printf("Ciudad:\n");
    scanf("%s", location);
    printf("Datos introducidos correctamente. Bienvenido/a, %s.", name);
}