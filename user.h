#ifndef LAB_0_USER_H
#define LAB_0_USER_H
#define MAX_LENGTH 25
#define MAIL_LENGTH 50
#define BARS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#define FILE_USERS "resources/users.txt"
#define FILE_REQUESTS "resources/requests.txt"

#endif //LAB_0_USER_H

/// Estructura de usuario
typedef struct{
    char name[MAX_LENGTH];          // Nombre real
    char surname[MAX_LENGTH];       // Primer apellido
    char username[MAX_LENGTH];      // Nombre de usuario
    char password[MAX_LENGTH];      // Contraseña
    int birth_date;                 // Año de nacimiento
    char email[MAIL_LENGTH];        // Correo electrónico
    char location[MAX_LENGTH];      // Ubicación
    int interests;                  // Intereses (recomendaremos usuarios afines)
} User;

/// Estructura de lista enlazada de usuario
typedef struct user_linked_list{
    User* user;                     // Usuario
    struct user_linked_list* next;  // Puntero al siguiente usuario
} UserLinked;

///Estructura de lista enlazada de peticiones
typedef struct user_request{
    char receiver[MAX_LENGTH];      // Usuario que recibe la solicitud
    char sender[MAX_LENGTH];        // Usuario que ha enviado la solicitud
    struct user_request* prev;      // Puntero a la anterior solicitud
    struct user_request* next;      // Puntero a la siguiente solicitud
} Request;


///Funciones internas inicio

UserLinked* init_list();

Request* init_queue(UserLinked* first_user);


///Funciones opciones menú principal

User* login(UserLinked* first);

int valid_login(char password[MAX_LENGTH], User* user);

User* fill_profile(UserLinked* first);

UserLinked* make_user_linked(char name[MAX_LENGTH], char surname[MAX_LENGTH], char username[MAX_LENGTH], char password[MAX_LENGTH],
                             int birth_date, char email[MAIL_LENGTH], char location[MAX_LENGTH], int interests, UserLinked* first);

int save_user(User* user);

void show_users(UserLinked* first);


///Funciones opciones de usuario

Request* make_request(char receiver[MAX_LENGTH], char sender[MAX_LENGTH], Request* first_req, UserLinked* first_user);

int save_requests(Request* first_req);

int view_requests(User* user, UserLinked* first);


///Funciones auxiliares

int get_num_users(UserLinked* first);

UserLinked* get_last_user(UserLinked* first);

UserLinked* search_user(char username[MAX_LENGTH], UserLinked* first);

