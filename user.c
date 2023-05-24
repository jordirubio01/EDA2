#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define FALSE (-1)
#define TRUE 1
#define SUCCESS 0
#define FILE_NOT_FOUND (-2)


/******** FUNCIONES INTERNAS INICIO Y FINAL ********/
/**
 *
 * @param f_name
 * @return
 *
 * Pre: Recibe una dirección de fichero con usuarios
 * Post: Lista dinámica con todos los usuarios creada; devuelve un puntero al primer usuario
 */
UserLinked* init_list() {
    UserLinked *first; // Primer usuario
    // Datos de cada usuario
    char name[MAX_LENGTH], surname[MAX_LENGTH], username[MAX_LENGTH];
    char email[MAIL_LENGTH], location[MAX_LENGTH], password[MAX_LENGTH];
    int birth_date, interests;

    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_USERS, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar los usuarios registrados!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
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

/**
 *
 * @param f_name
 * @return
 *
 * Pre: Recibe una dirección de fichero con usuarios
 * Post: Lista dinámica con todas las peticiones de amistad creada; devuelve un puntero a la primera solicitud
 */
Request* init_queue(UserLinked* first_user) {
    Request* first_req; // Primera solicitud
    // Datos de cada usuario
    char r_name[MAX_LENGTH], s_name[MAX_LENGTH];

    // Abrimos el fichero de solicitudes
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_REQUESTS, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las peticiones de amistad!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Primera solicitud
        fscanf(f, "%s %s", r_name, s_name);
        first_req = make_request(r_name, s_name, NULL, first_user);
        // Resto de solicitudes
        while (fscanf(f, "%s %s", r_name, s_name) == 2) { //Mientras los datos coincidan...
            make_request(r_name, s_name, first_req, first_user);
        }
        fclose(f); //Cerramos el fichero f
        return first_req;
    }
    return NULL; // Si ha habido algún error, devuelve NULL
}


/******** FUNCIONES PRINCIPALES ********/
/**** OPCIONES MENÚ INICIAL (Inicio de sesión, registro, listar usuarios) ****/
/**
 *
 * @param u
 * @return
 *
 * Pre: recibe un puntero al primer usuario de la lista
 * Post: si el usuario y la contraseña introducidos en la función son correctos, devuelve un puntero al usuario
 */
User* login(UserLinked* first){
    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("%s\n\t\t\t\t\t Inicio de Sesion\n%s\n", BARS, BARS);
    printf("\nUsuario:\n");
    scanf("%s", username);
    UserLinked* temp = search_user(username, first);
    if (temp == NULL){
        printf("El usuario '%s' NO existe\n", username);
        return NULL;
    }
    else{
        printf("Password:\n");
        scanf("%s", password);
        int status_login = valid_login(password, temp->user);
        if (status_login == TRUE){
            printf("Bienvenido %s\n", temp->user->name);
            return temp->user;
        }
        else{
            printf("\nContrase%ca incorrecta\n", 164);
            return NULL;
        }
    }
}

/**
 *
 * @param password
 * @param user
 * @return
 *
 * Pre: recibe un string correspondiente a la contraseña y una estructura de usuario
 * Post: si la contraseña es correcta, devuelve TRUE; en caso contrario, devuelve FALSE
 */
int valid_login(char password[MAX_LENGTH], User* user){
    if (strcmp(password, user->password) == 0){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

/**
* Pre: Recibe un puntero a un usuario
* Post: Los datos del usuario están completos
*/
User* fill_profile(UserLinked* first){
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
    save_user(new_user->user);
    return new_user->user;
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
 * Pre: Recibe los datos correctos de un nuevo usuario (nombre, apellido...) y un puntero al primer usuario
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
 * @param f
 * @param user
 *
 * Pre: Recibe un archivo y un usuario
 * Post: Los datos del usuario se han añadido al archivo
 */
int save_user(User* user){
    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_USERS, "a"); //Abrimos el fichero de usuarios en modo append (añadiremos una línea)
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


/**** OPCIONES DE USUARIO (Enviar solicitudes, gestionar solicitudes) - (opciones de publicaciones en "publications.c/h") ****/
/**
 *
 * @param receiver
 * @param sender
 * @param first
 * @return
 *
 * Pre: Recibe los datos correctos de una nueva solicitud (dos nombres de usuario) y un puntero a la primera solicitud
 * Post: Devuelve un puntero de tipo Request
 */
Request* make_request(char receiver[MAX_LENGTH], char sender[MAX_LENGTH], Request* first_req, UserLinked* first_user){
    if (search_user(receiver, first_user) != NULL){ // Si se ha encontrado un usuario con ese nombre...
        Request* req = (Request *) malloc(sizeof(Request)); // Reservamos memoria para una nueva solicitud
        strcpy(req->receiver, receiver);    // Guardamos el nombre del receptor
        strcpy(req->sender, sender);        // Guardamos el nombre del usuario
        req->next = NULL;   // La petición actual es la última por ahora

        // Si ya existe alguna solicitud...
        if (first_req != NULL){
            Request* temp = first_req;
            while (temp->next != NULL) { // Buscamos la última solicitud (la última no nula)
                temp = temp->next;
            }
            temp->next = req; // La nueva solicitud será la siguiente de la última
            req->prev = temp;
        }
        // Si no había ninguna solicitud, la anterior a esta es nula
        else req->prev = NULL;
        return req; // Devuelve la última solicitud
    }
    else return NULL;
}

/**
 *
 * @param username
 * @param user
 * @param first
 * @param f_name
 * @return
 *
 * Pre: recibe dos nombres de usuario
 * Post: la solicitud ha sido guardada en el fichero correspondiente; en caso contrario, devuelve error
 */
int save_requests(Request* first_req){
    Request* temp = first_req;
    // Actualizamos el fichero con las solicitudes
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_REQUESTS, "a"); // Abrimos el fichero de solicitudes en modo append (añadiremos una línea)
    if (f == NULL) f1 = FILE_NOT_FOUND; // Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las solicitudes de amistad!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso

    if (f1 == SUCCESS) { // Si el fichero ha sido abierto de forma exitosa...
        while (temp != NULL){
            fprintf(f, "\n%s %s", first_req->receiver, first_req->sender); // Imprimimos en el fichero los dos nombres
            temp = first_req->next;
        }
        fclose(f); // Cerramos el fichero f
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
}

/**
 *
 * @param user
 * @param first
 * @param f_name
 * @return
 *
 * Pre: recibe un puntero al usuario actual, un puntero al primer usuario de la lista y una dirección de fichero
 * Post: si el fichero se ha abierto correctamente, se imprimen por pantalla las solicitudes enviadas/recibidas
 */
int view_requests(User* user, UserLinked* first){
    char receiver[MAX_LENGTH], sender[MAX_LENGTH];
    int f_requests = 0;

    // Abrimos el fichero de solicitudes
    int f1 = SUCCESS;
    FILE *f = fopen(FILE_REQUESTS, "r"); //Abrimos el fichero input en modo read
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


/******** FUNCIONES AUXILIARES (implementadas en varias funciones) ********/
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