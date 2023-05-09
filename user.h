#ifndef LAB_0_USER_H
#define LAB_0_USER_H
#define MAX_LENGTH 20
#define MAIL_LENGTH 50

#endif //LAB_0_USER_H

// Estructura de usuario
typedef struct{
    char name[MAX_LENGTH];      // Nombre real
    char surname[MAX_LENGTH];  // Primer apellido
    char username[MAX_LENGTH];  // Nombre de usuario
    char password[MAX_LENGTH];  // Contraseña
    int birth_date;             // Fecha de nacimiento
    char email[MAIL_LENGTH];    // Correo electrónico
    char location[MAX_LENGTH];  // Ubicación
    char interests[5];          // Intereses (recomendaremos usuarios afines)
} User;

int valid_username(char username[MAX_LENGTH]);

void save_user(FILE* file, User* user);

User* fill_profile(User* user, FILE* file);
