#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define FALSE (-1)
#define TRUE 1
#define SUCCESS 0
#define FILE_NOT_FOUND (-2)


// FUNCIONES INTERNAS
/**
 *
 * @param f_name
 * @return
 *
 * Pre: Recibe una dirección de fichero con usuarios
 * Post: Lista dinámica con todos los usuarios creada; devuelve un puntero al primer usuario
 */
UserLinked* init_list(char f_name[MAX_LENGTH]) {
    UserLinked *first; // Primer usuario
    // Datos de cada usuario
    char name[MAX_LENGTH], surname[MAX_LENGTH], username[MAX_LENGTH];
    char email[MAIL_LENGTH], location[MAX_LENGTH], password[MAX_LENGTH];
    int birth_date, interests;

    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(f_name, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("Error al recuperar los usuarios registrados!\n"); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Primer usuario
        fscanf(f, "%s %s %s %s %d %s %s %d", name, surname, username, password, &birth_date, email, location, &interests);
        first = make_user_linked(name, surname, username, password, birth_date, email, location, interests, NULL);
        // Resto de usuarios
        while (fscanf(f, "%s %s %s %s %d %s %s %d", name, surname, username, password, &birth_date, email, location, &interests) > 7) { //Mientras los datos coincidan...
            make_user_linked(name, surname, username, password, birth_date, email, location, interests, first);
        }
        fclose(f); //Cerramos el fichero f
        return first;
    }
    return NULL; // Si ha habido algún error, devuelve NULL
}

// FUNCIONES USUARIO
/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
User* fill_profile(char f_name[MAX_LENGTH], UserLinked* first){
    char name[MAX_LENGTH], surname[MAX_LENGTH], username[MAX_LENGTH];
    char email[MAIL_LENGTH], location[MAX_LENGTH], password[MAX_LENGTH];
    int birth_date, interests;

    printf("Para empezar, introduce un nombre de usuario y contrase%ca\n", 164);
    printf("Usuario:\n");
    scanf("%s", username);
    while (search_user(username, first) != NULL){ // Mientras el nombre de usuario coincida con alguno existente...
        printf("El nombre de usuario introducido no est%c disponible. Introduce otro:\n", 160);
        scanf("%s", username);
    }
    //Tenemos que comprobar que la contraseña sea válida (igual que el nombre de usuario)
    printf("Contrase%ca:\n", 164);
    scanf("%s", password);
    printf("Tu nombre de usuario es %s. Cu%cntanos m%cs sobre ti...\n", username, 130, 160);

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
    printf("Intereses [Introduce 5 cifras sin espacios]\n(1-MUSICA, 2-DEPORTES, 3-GASTRONOMIA, 4-VIAJES, 5-COCHES, 6-CINE, 7-FIESTA, 8-CIENCIA, 9-OTROS)\n");
    scanf("%d", &interests);

    printf("Datos introducidos correctamente. Bienvenido/a, %s. Puedes iniciar sesi%cn cuando quieras.\n%s\n", name, 162, BARS);

    UserLinked* new_user = make_user_linked(name, surname, username, password, birth_date, email, location, interests, first);
    save_user(f_name, new_user->user);
    return new_user->user;
}

void show_users(UserLinked* first){
    int total = get_num_users(first);
    UserLinked* temp = first;
    printf("\t\t\t\tLista de usuarios actuales (%d registrados)\n\n%s\n", get_num_users(first), BARS);
    printf("Nombre\tApellido\tNombre de usuario\tFecha de nacimiento\tEmail\t\t\tLocalidad\n");
    while (temp != NULL){
        printf("%s\t%s\t\t%s\t\t\t%d\t\t%s\t\t%s\n", temp->user->name, temp->user->surname, temp->user->username, temp->user->birth_date, temp->user->email, temp->user->location);
        // FUNCIÓN PARA IMPRIMIR INTERESES (a partir de valores asociados)
        temp = temp->next;
    }
    printf("%s\n", BARS);
}

/**
 *
 * @param f
 * @param user
 *
 * Pre: Recibe un archivo y un usuario
 * Post: Los datos del usuario se han añadido al archivo
 */
int save_user(char f_name[MAX_LENGTH], User* user){
    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(f_name, "a"); //Abrimos el fichero de usuarios en modo append (añadiremos una línea)
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("Error al recuperar los usuarios registrados!\n"); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Resto de usuarios
        fprintf(f, "\n%s %s %s %s %d %s %s %d", user->name, user->surname, user->username, user->password,
                user->birth_date, user->email, user->location, user->interests);
        fclose(f); //Cerramos el fichero f
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
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
                               int birth_date, char email[MAIL_LENGTH], char location[MAX_LENGTH], int interests, UserLinked* first){
    UserLinked* c = (UserLinked*) malloc(sizeof(UserLinked)); // Allocate memory for a new ClientLinked
    c->user = (User*) malloc(sizeof(User)); // Allocate memory for its Client variable
    strcpy(c->user->name, name);
    strcpy(c->user->surname, surname);
    strcpy(c->user->username, username);
    strcpy(c->user->password, password);
    c->user->birth_date = birth_date;
    strcpy(c->user->email, email);
    strcpy(c->user->location, location);
    c->user->interests = interests;
    c->next = NULL;
    if (first != NULL){ //Si aún no existe ningún usuario...
        UserLinked *last = get_last_user(first);
        last->next = c;
    }
    return c;
}

/**
 *
 * @param u
 * @return
 *
 * Pre: Recibe un puntero al primer usuario registrado
 * Post: Devuelve el número de usuarios
 */
int get_num_users(UserLinked* first){ // La función devuelve el número de usuarios existentes
    int user_index = 0;
    UserLinked* temporary = first;
    while (temporary != NULL){
        user_index++;
        temporary = temporary->next;
    }
    return user_index;
}

/**
 *
 * @param first
 * @return
 *
 * Pre: Recibe un puntero al primer usuario
 * Post: Devuelve un puntero al último usuario registrado
 *
 */
UserLinked* get_last_user(UserLinked* first){
    UserLinked* temp = first;
    while (temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}


/**
 *
 * @param username
 * @param first
 * @return
 *
 * Pre: Recibe una cadena de caracteres y un puntero al primer usuario
 * Post: Si se ha encontrado el usuario, devuelve un puntero; en caso contrario, devuelve NULL
 */
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

/**
 *
 * @param username
 * @param user
 * @param first
 * @param f_name
 * @return
 *
 * Pre: recibe un nombre de usuario, puntero al usuario actual, puntero al primer usuario y dirección del fichero de usuarios
 * Post: si se ha encontrado el usuario, la solicitud ha sido guardada en el fichero correspondiente; en caso contrario, devuelve error
 */
int request_friend(char username[MAX_LENGTH], User* user, UserLinked* first, char f_name[MAX_LENGTH]){
    if (search_user(username, first) != NULL){ // Si se ha encontrado un usuario con ese nombre...

        // Abrimos el fichero de solicitudes de amistad
        int f1 = SUCCESS, exit = 0;
        FILE *f = fopen(f_name, "a"); // Abrimos el fichero de solicitudes en modo append (añadiremos una línea)
        if (f == NULL) f1 = FILE_NOT_FOUND; // Si el archivo es NULL, mandamos un error
        if (f1 == FILE_NOT_FOUND)
            printf("Error al recuperar los usuarios registrados!\n"); //Si fa es NULL, mostramos un mensaje de aviso

        if (f1 == SUCCESS) { // Si el fichero ha sido abierto de forma exitosa...
            fprintf(f, "\n%s %s", username, user->name); // Imprimimos en el fichero los dos nombres
            fclose(f); // Cerramos el fichero f
            return SUCCESS;
        }
        return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
    }
}

int view_requests(User* user, UserLinked* first, char f_name[MAX_LENGTH]){
    char receiver[MAX_LENGTH], sender[MAX_LENGTH];
    int f_requests = 0;

    // Abrimos el fichero de solicitudes
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(f_name, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("Error al recuperar los usuarios registrados!\n"); //Si fa es NULL, mostramos un mensaje de aviso

    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Primer usuario
        while (fscanf(f, "%s %s", receiver, sender) == 2) { //Mientras los datos coincidan...
            if (strcmp(user->username, receiver) == 0){
                printf("%s quiere ser tu amigo/a.\n", sender);
                f_requests++;
            }
            else if (strcmp(user->username, sender) == 0) printf("Tu solicitud de amistad con %s está pendiente.\n", receiver);
        }
        fclose(f); //Cerramos el fichero f
        if (f_requests == 0) printf("En este momento no has recibido ninguna solicitud de amistad.");
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
}

int valid_login(char password[MAX_LENGTH], User* user){
    if (strcmp(password, user->password) == 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

User* login(UserLinked* u){
    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("%s\n\t\t\t\t\t Inicio de Sesion\n%s\n" BARS, BARS);
    printf("Usuario:\n");
    scanf("%s", username);
    UserLinked* temp = search_user(username, u);
    if (temp == NULL){
        printf("El usuario '%s' NO existe\n", username);
    }
    else{
        printf("Contraseña:\n");
        scanf("%s", password);
        int status_login = valid_login(password, temp->user);
        if (status_login == TRUE){
            printf("Bienvenido %s", temp->user->name);
            return temp->user;
        }
        else{
            printf("Contraseña incorrecta");
            return NULL;
        }
    }
}

