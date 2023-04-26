#ifndef LAB_0_USER_H
#define LAB_0_USER_H

#endif //LAB_0_USER_H

typedef struct{
    char name;
    char username;
    int birth_date;
    char email;
    char location;
    char interests[5];
} User;

int fill_profile(User* user, FILE* file);
