#ifndef LAB_0_MENU_H
#define LAB_0_MENU_H
#include "dictionary.h"
#define MAX_SIZE 10

#endif //LAB_0_MENU_H

/// Estructura de pila
typedef struct{
    int data[MAX_SIZE];
    int top;
}Stack;

/// Funciones para el menú

void show_first_menu();

void show_full_menu();

void load_option(int op, UserLinked* l_users, Request* l_requests, ActivityLinked* activities, Dictionary* dictionary, Stack* stack);

void load_user_option(int op, UserLinked* l_users, User* current_user, Request* l_requests, ActivityLinked* activities);

/// Funciones para la pila (stack)

Stack* init_stack();

int isEmpty(Stack* stack);

int isFull(Stack* stack);

Stack* push(Stack* stack, int element);

Stack* pop(Stack* stack);

int top(Stack* stack);