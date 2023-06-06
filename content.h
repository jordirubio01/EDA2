#include "user.h"
#ifndef LAB_0_CONTENT_H
#define LAB_0_CONTENT_H

#endif //LAB_0_CONTENT_H


typedef struct activity_linked_list{
    Activity* activity;
    struct activity_linked_list* next;
}ActivityLinked;

ActivityLinked* make_activity_linked(char name[MAX_LENGTH], int type, char location[MAX_LENGTH], char schedule[MAX_LENGTH], char review[MAX_LENGTH_REVIEW], int stars, double price, User* user, ActivityLinked* first);
ActivityLinked* get_last_activity(ActivityLinked* first);
ActivityLinked* new_content(ActivityLinked* first, User* user);
ActivityLinked* init_activity_list();

int save_activity(Activity* activity);

void save_content_at_user(UserLinked* user, ActivityLinked* content);