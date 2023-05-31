#include "user.h"
#ifndef LAB_0_CONTENT_H
#define LAB_0_CONTENT_H
#define MAX_LENGTH_REVIEW 1000
#endif //LAB_0_CONTENT_H

// Estructura de actividades
typedef struct{
    char name;
    char type;      // Monumento, Gastronomía, Hospedaje, Deporte, Transporte, Otros
    char location;  // Ubicación
    char schedule;  // Horarios
    double price;   // Precio
    int stars;      // Valoración (0-5)
    char review;    // Reseña, Opiniones, Comentarios
    User* user;     // Usuario
} Activity;

typedef struct activity_linked_list{
    Activity* activity;
    struct activity_linked_list* next;
}ActivityLinked;

//ActivityLinked* make_activity_linked(char name[MAX_LENGTH] char type[MAX_LENGTH], char location[MAX_LENGTH], char schedule[MAX_LENGTH], char review[MAX_LENGTH_REVIEW], int stars, double price, User* user, UserLinked* first);