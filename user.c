#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define FALSE (-1)
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

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
User* fill_profile(FILE* f_user){
    char name[MAX_LENGTH], surname[MAX_LENGTH], username[MAX_LENGTH];
    char email[MAIL_LENGTH], location[MAX_LENGTH], password[MAX_LENGTH], interests[MAX_LENGTH*5];
    int birth_date;
    printf("Introduce tu nombre:\n");
    scanf("%s", name);
    printf("Introduce tu apellido:\n");
    scanf("%s", surname);
    printf("Fecha de nacimiento [ddmmaaaa]:\n");
    scanf("%d", &birth_date);
    printf("Email:\n");
    scanf("%s", email);
    printf("Ciudad:\n");
    scanf("%s", location);

    printf("Datos introducidos correctamente. Bienvenido/a, %s.\n", name);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("%s, ahora debes elegir un nombre de usuario y un password.\n", name);
    printf("Usuario:\n");
    scanf("%s", username);
    while (valid_username(username) == FALSE){
        printf("El nombre de usuario introducido no está disponible. Introduzca otro:\n");
        scanf("%s", username);
    }
    //Tenemos que comprobar que la contraseña sea válida (igual que el nombre de usuario)
    printf("Password:\n");
    scanf("%s", password);
    UserLinked* new_user = make_user_linked(name, surname, username, password, birth_date, email, location, interests);
    return new_user->user;
}

/**
 *
 * @param f
 * @param user
 *
 * Pre: Recibe un archivo y un usuario
 * Post: Los datos del usuario se han añadido al archivo
 */
void save_user(FILE* f, User* user){
    fprintf(f, "%s %s %s %s\n", user->name, user->surname, user->username, user->password);
}


UserLinked* make_head(User* u){
    UserLinked* head = NULL;
    head = (UserLinked*) malloc(sizeof(UserLinked));
    //GUARDAMOS LOS DATOS//
    head->user = u;
    return head;
}


/**
 *
 * @param name
 * @param surname
 * @param username
 * @param password
 * @param birth_date
 * @param email
 * @param location
 * @param interests
 *
 * Pre: Recibe los datos correctos de un nuevo usuario (nombre, apellido...)
 * Post: Devuelve un puntero de tipo UserLinked
 */
UserLinked* make_user_linked(char name[MAX_LENGTH], char surname[MAX_LENGTH], char username[MAX_LENGTH], char password[MAX_LENGTH],
                               int birth_date, char email[MAIL_LENGTH], char location[MAX_LENGTH], char interests[MAX_LENGTH*5], UserLinked* first){
    UserLinked* c = (UserLinked*) malloc(sizeof(UserLinked)); // Allocate memory for a new ClientLinked
    c->user = (User*) malloc(sizeof(User)); // Allocate memory for its Client variable
    strcpy(c->user->name, name);
    strcpy(c->user->surname, surname);
    strcpy(c->user->username, username);
    strcpy(c->user->password, password);
    c->user->birth_date = birth_date;
    strcpy(c->user->email, email);
    strcpy(c->user->location, location);
    strcpy(c->user->interests, interests);
    c->next = NULL;
    UserLinked* last = get_last_user(first);
    last->next = c;

    return c;
}


int get_num_users(UserLinked* u){ // La función devuelve el número de usuarios existentes
    int user_index = 0;
    UserLinked* temporary = (UserLinked *) u->user;
    while (temporary != NULL){
        user_index++;
        temporary = temporary->next;
    }
    return user_index;
}

UserLinked* get_last_user(UserLinked* first){

}

UserLinked* search_user(char username[MAX_LENGTH], UserLinked* first){ //La función busca si el usuario recibido existe
    UserLinked* temp = first;
    while (temp != NULL){
        if(strcmp(username, temp->user->username) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}