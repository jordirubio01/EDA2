#include "user.h"

/******** FUNCIONES INTERNAS INICIO Y FINAL ********/
/**
 *
 * @param f_name
 * @return
 *
 * Pre: -
 * Post: Lista dinámica con todos los usuarios creada; devuelve un puntero al primer usuario
 */
UserLinked* init_list() {
    clock_t start, end; // Variables para medir el tiempo que se ejecuta la función
    float total_time;
    start = clock();    // Empieza el contador
    UserLinked *first;  // Primer usuario
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
        end = clock(); // Termina el contador
        total_time = ((float)(end-start)) / CLOCKS_PER_SEC; // Diferencia entre inicio y final
        printf("Usuarios recuperados en %f segundos\n", total_time);
        return first;
    }
    return NULL; // Si ha habido algún error, devuelve NULL
}

/**
 *
 * @param first_user
 * @return
 *
 * Pre: recibe un puntero al primer usuario
 * Post: todos los usuarios contienen sus relaciones de amistad
 */
int init_friends(UserLinked* first_user){
    clock_t start, end; // Variables para medir el tiempo que se ejecuta la función
    float total_time;
    start = clock();    // Empieza el contador

    // Variables temporales
    UserLinked* temp_user;
    char user1[MAX_LENGTH], user2[MAX_LENGTH];

    // Abrimos el fichero de amigos
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_FRIENDS, "r"); // Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; // Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las relaciones de amistad entre usuarios!\n", 173); // Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { // Si el fichero ha sido abierto de forma exitosa...
        // Escaneamos el fichero de amigos
        fscanf(f, "%s %s", user1, user2); // Ignoramos la primera línea ("User1 User2")
        while (fscanf(f, "%s %s", user1, user2) == 2) { // Mientras los datos coincidan...
            temp_user = search_user(user1, first_user); // Buscamos el usuario 1
            make_friends(temp_user->user, user2, first_user); // Añadimos la relación al perfil de los dos usuarios
        }
        fclose(f); //Cerramos el fichero f
        end = clock(); // Termina el contador
        total_time = ((float)(end-start)) / CLOCKS_PER_SEC; // Diferencia entre inicio y final
        printf("Relaciones de amistad recuperadas en %f segundos\n", total_time);
        return SUCCESS;
    }
    return -1; // Si ha habido algún error, devuelve NULL

}


/**
 *
 * @param f_name
 * @return
 *
 * Pre: Recibe un puntero al primer usuario
 * Post: Lista dinámica con todas las peticiones de amistad creada; devuelve un puntero a la primera solicitud
 */
Request* init_queue(UserLinked* first_user) {
    clock_t start, end;
    float total_time;
    start = clock();
    Request* first_req; // Primera solicitud
    // Datos de cada usuario
    char r_name[MAX_LENGTH], s_name[MAX_LENGTH];

    // Abrimos el fichero de solicitudes
    int f1 = SUCCESS;
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
        end = clock(); // Termina el contador
        total_time = ((float)(end-start)) / CLOCKS_PER_SEC; // Diferencia entre inicio y final
        printf("Solicitudes de amistad recuperadas en %lf segundos\n", total_time);
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
    printf("%s\n\t\t\t\t\t Inicio de Sesi%cn\n%s\n", BARS, 162, BARS);
    printf("Usuario:\n");
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
            printf("Bienvenido/a, %s.\n", temp->user->name);
            return temp->user;
        }
        else{
            printf("Contrase%ca incorrecta.\n", 164);
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
    UserLinked* c = (UserLinked*) malloc(sizeof(UserLinked)); // Reservamos memoria para UserLinked
    c->user = (User*) malloc(sizeof(User)); // Reservamos memoria para User
    strcpy(c->user->name, name);
    strcpy(c->user->surname, surname);
    strcpy(c->user->username, username);
    strcpy(c->user->password, password);
    c->user->birth_date = birth_date;
    strcpy(c->user->email, email);
    strcpy(c->user->location, location);
    c->user->interests = interests;
    for (int i = 0; i < 25; i++){
        strcpy(c->user->friends[i], " ");
    }
    c->user->content = NULL;
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
        printf("%cError al recuperar los usuarios registrados!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Guardamos en el fichero el nuevo usuario
        fprintf(f, "\n%s %s %s %s %d %s %s %d", user->name, user->surname, user->username, user->password,
                user->birth_date, user->email, user->location, user->interests);
        fclose(f); //Cerramos el fichero f
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
}

/**
 *
 * @param first
 *
 * Pre: Recibe un puntero al primer usuario
 * Post: Los datos de todos los usuarios han sido imprimidos
 */
void show_users(UserLinked* first){
    int total = get_num_users(first);
    UserLinked* temp = first;
    printf("\t\t\t\tLista de usuarios actuales (%d registrados)\n\n%s\n", get_num_users(first), BARS);
    printf("Nombre\tApellido\tNombre de usuario\tFecha de nacimiento\tEmail\t\t\tLocalidad\n");
    while (temp != NULL){
        printf("%s\t%s\t\t%s\t\t       %d\t\t%s\t\t%s\n", temp->user->name, temp->user->surname, temp->user->username, temp->user->birth_date, temp->user->email, temp->user->location);
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
    UserLinked* rec_user = search_user(receiver, first_user);
    if (rec_user != NULL){ // Si se ha encontrado un usuario con ese nombre...
        // Comprobamos que la solicitud no esté repetida
        Request* temp = first_req;
        // ¿Ya se ha enviado o recibido una solicitud de esa persona?
        while (temp != NULL){ // Por cada solicitud...
            if ((strcmp(temp->receiver, receiver) == 0 && strcmp(temp->sender, sender) == 0 ) || (strcmp(temp->receiver, sender) == 0 && strcmp(temp->sender, receiver) == 0 )){
                printf("Tienes una solicitud pendiente con %s (accede a '2. Gestionar amigos/as' para m%cs informaci%cn).\n", receiver, 160, 162); // Imprimimos por pantalla
                return NULL; // Devolvemos NULL
            }
            temp = temp->next;
        }

        // ¿Ya es amigo/a de esa persona?
        for (int i = 0; i<25; i++){ // Por cada elemento en la lista de amigos...
            if (strcmp(rec_user->user->friends[i], sender) == 0){  // Si ya son amigos...
                printf("%c%s ya es tu amigo/a!\n", 173, receiver); // Imprimimos por pantalla
                return NULL; // Devolvemos NULL
            }
        }

        Request* req = (Request *) malloc(sizeof(Request)); // Reservamos memoria para una nueva solicitud
        strcpy(req->receiver, receiver);    // Guardamos el nombre del receptor
        strcpy(req->sender, sender);        // Guardamos el nombre del usuario
        req->next = NULL;   // La petición actual es la última por ahora

        // Si ya existe alguna solicitud...
        if (first_req != NULL){
            temp = first_req;
            while (temp->next != NULL) { // Buscamos la última solicitud (la última no nula)
                temp = temp->next;
            }
            temp->next = req; // La nueva solicitud será la siguiente de la última
            req->prev = temp;
        }
        // Si no había ninguna solicitud, la anterior a esta es nula
        else req->prev = NULL;
        printf("Solicitud enviada.\n");
        return req; // Devuelve la última solicitud
    }
    else if (strcmp(receiver, "Receiver") == 0 && strcmp(sender, "Sender") == 0){ // Si simplemente es el encabezado...
        Request* req = (Request *) malloc(sizeof(Request)); // Reservamos memoria
        strcpy(req->receiver, receiver);    // Guardamos "Receiver"
        strcpy(req->sender, sender);        // Guardamos "Sender"
        req->next = NULL;   // El elemento actual es el último por ahora
        return req;
    }
    else{
        printf("No se ha encontrado ningun usuario llamado %s.\n", receiver);
        return NULL;
    }
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
    int f1 = SUCCESS;
    remove(FILE_REQUESTS);
    FILE *f = fopen(FILE_REQUESTS, "a"); // Abrimos el fichero de solicitudes en modo write (actualizaremos el fichero)
    if (f == NULL) f1 = FILE_NOT_FOUND; // Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las solicitudes de amistad!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso

    if (f1 == SUCCESS) { // Si el fichero ha sido abierto de forma exitosa...
        while (temp != NULL){
            fprintf(f, "%s %s\n", temp->receiver, temp->sender); // Imprimimos en el fichero los dos nombres
            temp = temp->next;
        }
        fclose(f); // Cerramos el fichero f
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
}

/**
 *
 * @param user
 *
 * Pre: recibe un puntero al usuario actual
 * Post: todos los amigos se han imprimido por pantalla; si no tiene amigos agregados recibe un mensaje
 */
void view_friends(User* user){
    int i = 0;
    if (strcmp(user->friends[i], " ") != 0){
        printf("%s\n\t\t\t\t\t\tLista de amigos\n%s\n", BARS, BARS);
        while (strcmp(user->friends[i], " ") != 0){
            printf("- %s\n", user->friends[i]);
            i++;
        }
    }
    else printf("Actualmente no tienes amigos agregados.\n");
}

/**
 *
 * @param user
 * @param user2
 * @param first_u
 *
 * Pre: recibe un puntero al usuario1, el nombre del usuario2 y un puntero al primer usuario de todos
 * Post: la relación de ambos usuarios ha sido actualizada
 */
void make_friends(User* user, char user2[MAX_LENGTH], UserLinked* first_u){
    int i = 0, code = 0;
    while (code == 0) { // Entramos en bucle hasta añadir amigo correctamente
        if (strcmp(user->friends[i], " ") == 0){ // Si encontramos un elemento vacío...
            strcpy(user->friends[i], user2); // Añadimos el nuevo amigo
            code = 1;   // Salimos del bucle
        }
        i++;
    }
    i = 0, code = 0; // Restablecemos el índice y el código de éxito
    UserLinked* s_user = search_user(user2, first_u); // Buscamos el otro usuario
    while (code == 0){  // Entramos en bucle hasta añadir amigo correctamente
        if (strcmp(s_user->user->friends[i], " ") == 0) { // Si encontramos un elemento vacío...
            strcpy(s_user->user->friends[i], user->username); // Añadimos el nuevo amigo
            code = 1;   // Salimos del bucle
        }
        i++;
    }
}


int save_friends(char user1[MAX_LENGTH], char user2[MAX_LENGTH]){
    // Abrimos el fichero de amigos
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_FRIENDS, "a"); //Abrimos el fichero de usuarios en modo append (añadiremos una línea)
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las relaciones de amistad entre usuarios!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Guardamos en el archivo la nueva relación de amistad
        fprintf(f, "\n%s %s", user1, user2);
        fclose(f); //Cerramos el fichero f
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
 * Pre: recibe un puntero al usuario actual, un puntero al primer usuario de la lista y un puntero a la lista de peticiones
 * Post: si el fichero se ha abierto correctamente, se imprimen por pantalla las solicitudes enviadas/recibidas
 */
void view_requests(User* user, UserLinked* first_user, Request* first_req){
    char receiver[MAX_LENGTH], sender[MAX_LENGTH];
    Request* temp = first_req;
    int any_req = FALSE;

    // Buscamos peticiones recibidas y enviadas
    while (temp != NULL){
        if(strcmp(user->username, temp->receiver) == 0){
            accept_deny_req(user, temp, 1, first_user);
            any_req = TRUE;
        }
        else if(strcmp(user->username, temp->sender) == 0) {
            accept_deny_req(user, temp, 2, first_user);
            any_req = TRUE;
        }
        temp = temp->next;
    }
    if (any_req == FALSE) printf("Actualmente no has enviado ni recibido solicitudes de amistad.\n");
    // Guardamos todos los cambios
    save_requests(first_req);
}

/**
 *
 * @param user
 * @param req
 * @param rec_sent
 * @param first_u
 *
 * Pre: recibe un puntero al usuario actual, la lista de peticiones, un entero (1 o 2) y un puntero al primer usuario
 * Post: se han aceptado o rechazado las solicitudes del usuario actual
 */
void accept_deny_req(User* user, Request* req, int rec_sent, UserLinked* first_u){
    int yes_no, i = 0, code = 0;

    // Si la petición ha sido recibida...
    if (rec_sent == 1){
        // Preguntamos si quiere aceptar o rechazar
        printf("%s quiere ser tu amigo/a. %cQuieres aceptar? (Responde 0 para eliminar o 1 para aceptar)\n", req->sender, 168);
        scanf("%d", &yes_no);
        if (yes_no == 0){ // Si quiere rechazarla...
            printf("Solicitud eliminada.\n"); // Imprimimos la decisión
        }
        else if (yes_no == 1){  // Si quiere aceptarla...
            make_friends(user, req->sender, first_u);  // Añadimos la relación de amistad en ambos perfiles
            save_friends(user->username, req->sender); // Guardamos la relación de amistad en el fichero
            printf("Ahora %s es tu amigo/a.\n", req->sender); // Imprimimos mensaje de éxito
        }
        // En cualquier caso, acabamos eliminando las solicitudes
        if (req->prev != NULL) req->prev->next = req->next;
        if (req->next != NULL) req->next->prev = req->prev;
        req = NULL;
    }

    // Si la petición ha sido enviada...
    else if (rec_sent == 2){
        // Preguntamos si quiere eliminarla antes de ser aceptada
        printf("Tu solicitud de amistad con %s est%c pendiente. %cQuieres eliminarla? (Responde 1 para eliminar o 0 para cancelar)\n", req->receiver, 160, 168);
        scanf("%d", &yes_no);
        if (yes_no == 1){ // Si quiere eliminarla...
            // Eliminamos la solicitud
            if (req->prev != NULL) req->prev->next = req->next;
            if (req->next != NULL) req->next->prev = req->prev;
            req = NULL;
            printf("Solicitud eliminada.\n"); // Imprimimos mensaje de éxito
        }
    }
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