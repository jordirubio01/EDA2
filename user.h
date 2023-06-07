#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef LAB_0_USER_H
#define LAB_0_USER_H
#define MAX_LENGTH 25
#define MAIL_LENGTH 50
#define MAX_LENGTH_REVIEW 500
#define BARS "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
#define FILE_USERS "resources/users.txt"
#define FILE_REQUESTS "resources/requests.txt"
#define FILE_CONTENT "resources/content.txt"
#define FILE_FRIENDS "resources/friends.txt"

#define FALSE 0
#define TRUE 1
#define SUCCESS 0
#define FILE_NOT_FOUND (-2)

#endif //LAB_0_USER_H

/// Estructura de actividades
typedef struct{
    char name[MAX_LENGTH];
    int type;                       // Monumento, Gastronomía, Hospedaje, Deporte, Transporte, Otros
    char location[MAX_LENGTH];      // Ubicación
    char schedule[MAX_LENGTH];      // Horarios
    double price;                   // Precio
    int stars;                      // Valoración (0-5)
    char review[MAX_LENGTH_REVIEW]; // Reseña, Opiniones, Comentarios
    char username[MAX_LENGTH];
} Activity;

/// Estructura de lista enlazada de actividades
typedef struct activity_linked_list{
    Activity* activity;
    struct activity_linked_list* next;
}ActivityLinked;


/// Estructura de usuario
typedef struct {
    char name[MAX_LENGTH];          // Nombre real
    char surname[MAX_LENGTH];       // Primer apellido
    char username[MAX_LENGTH];      // Nombre de usuario
    char password[MAX_LENGTH];      // Contraseña
    int birth_date;                 // Año de nacimiento
    char email[MAIL_LENGTH];        // Correo electrónico
    char location[MAX_LENGTH];      // Ubicación
    int interests;                  // Intereses (recomendaremos usuarios afines)
    char friends[25][MAX_LENGTH];   // Amigos y amigas (máximo 50)
    ActivityLinked* content;
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

int init_friends(UserLinked* first_user);

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

void view_friends(User* user);

void make_friends(User* user, char user2[MAX_LENGTH], UserLinked* first_u);

int save_friends(char user1[MAX_LENGTH], char user2[MAX_LENGTH]);

void view_requests(User* user, UserLinked* first_user, Request* first_req);

void accept_deny_req(User* user, Request* req, int rec_sent, UserLinked* first_u);


///Funciones auxiliares

int get_num_users(UserLinked* first);

UserLinked* get_last_user(UserLinked* first);

UserLinked* search_user(char username[MAX_LENGTH], UserLinked* first);

