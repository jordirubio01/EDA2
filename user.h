#ifndef LAB_0_USER_H
#define LAB_0_USER_H

#endif //LAB_0_USER_H

typedef struct{
    char name;
    char lastname;
    char username;
    int birth_date;
    char email;
    char location;
    char interests[5];
} User;

int valid_password(int password);

void save_username(FILE* file, char username);

void read_usernames(FILE* file);

int fill_profile(User* user, FILE* file);
