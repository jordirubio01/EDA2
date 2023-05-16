#ifndef LAB_0_USER_H
#define LAB_0_USER_H
#define MAX_LENGTH 20
#define MAIL_LENGTH 50
#define BARS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

#endif //LAB_0_USER_H

// Estructura de usuario
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

// Estructura de lista enlazada de usuario
typedef struct user_linked_list{
    User* user;                     // Usuario
    struct user_linked_list* next;  // Puntero al siguiente usuario
} UserLinked;

UserLinked* init_list(char f_name[MAX_LENGTH]);

User* fill_profile(char file[MAX_LENGTH], UserLinked* first);

int valid_username(char username[MAX_LENGTH]);

UserLinked* make_user_linked(char name[MAX_LENGTH], char surname[MAX_LENGTH], char username[MAX_LENGTH], char password[MAX_LENGTH],
                             int birth_date, char email[MAIL_LENGTH], char location[MAX_LENGTH], int interests, UserLinked* first);

void save_user(FILE* file, User* user);

UserLinked* make_head(User* u);

UserLinked* get_last_user(UserLinked* first);

int get_num_users(UserLinked* u);

UserLinked* search_user(char username[MAX_LENGTH], UserLinked* u);

