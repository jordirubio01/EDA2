#ifndef LAB_0_USER_H
#define LAB_0_USER_H
#define MAX_LENGHT 20
#define MAIL_LENGHT 50

#endif //LAB_0_USER_H

typedef struct{
    char name[MAX_LENGHT];
    char lastname[MAX_LENGHT];
    char username[MAX_LENGHT];
    char password[MAX_LENGHT];
    int birth_date;
    char email[MAIL_LENGHT];
    char location[MAX_LENGHT];
    char interests[5];
} User;

int valid_username(char username[MAX_LENGHT]);

void save_usernames(FILE* file, char username);

int fill_profile(User* user, FILE* file);
