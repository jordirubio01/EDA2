#ifndef LAB_0_MENU_H
#define LAB_0_MENU_H
#include "user.h"

#endif //LAB_0_MENU_H

void show_first_menu();

void show_full_menu();

void load_option(int op, UserLinked* l_users, Request* l_requests);

void load_user_option(int op, UserLinked* l_users, User* current_user, Request* l_requests);