#include <stdio.h>
#include "user.h"
#define FALSE -1

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
int valid_password();
int valid_username(int username){
    FILE* f_username = fopen("EDA 2/usernames.txt", "r");
    fscanf()
}
void save_usernames(FILE* file, int username);


int fill_profile(User* user, FILE* f_user){
    char name[MAX_LENGHT], lastname[MAX_LENGHT], username[MAX_LENGHT], email[50], location[MAX_LENGHT]; int birth_date;
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
    printf("%s, ahora debes elegir un nombre de usuario y una contraseña.\n", name);
    printf("Usuario:\n");
    scanf("%s", username);
    if (valid_username == FALSE);
}