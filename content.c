#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "content.h"




ActivityLinked* make_activity_linked(char name[MAX_LENGTH], int type, char location[MAX_LENGTH], char schedule[MAX_LENGTH],
                                     char review[MAX_LENGTH_REVIEW], int stars, double price, char username[MAX_LENGTH], ActivityLinked* first){
    ActivityLinked* c = (ActivityLinked*) malloc(sizeof(ActivityLinked));
    strcpy(&c->activity->name, name);
    strcpy(&c->activity->location, location);
    strcpy(&c->activity->schedule, schedule);
    strcpy(&c->activity->review, review);
    c->activity->stars = stars;
    c->activity->type = type;
    c->activity->price = price;
    c->next = NULL;
    if (first != NULL){
        ActivityLinked* last = get_last_activity(first);
        last->next = c;
    }
}

ActivityLinked* get_last_activity(ActivityLinked* first){
    ActivityLinked* temp = first;
    while (temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}

ActivityLinked* new_content(ActivityLinked* first, User* user){
    char name[MAX_LENGTH], location[MAX_LENGTH], schedule[MAX_LENGTH], review[MAX_LENGTH_REVIEW];
    int stars, type;
    double price;

    printf("Rellena la siguiente ficha t%cnica\n%s", 130, BARS);
    printf("Nombre:");
    scanf("%s", name);
    printf("Localidad");
    scanf("%s", location);
    printf("Horario [hh:mm - hh:mm]");
    scanf("%s", schedule);
    printf("Precio:");
    scanf("%2lf", &price);
    printf("1-Ciencia\n2-Gastronomia\n3-Cultura\n4-Deportes\n5-Musica\n%cmbito[Introduce Numero]:", 181);
    scanf("%d", &type);
    printf("Opinion:");
    scanf("%s", review);
    printf("Valoraci%cn [Estrellas (1-5)]:", 162);
    scanf("%d", &stars);

    ActivityLinked* new_activity = make_activity_linked(name, type, location, schedule, review, stars, price, user, first);
    save_activity(new_activity->activity);
}*/

/*ActivityLinked* init_activity_list() {
    ActivityLinked *first; // Primer usuario
    // Datos de cada usuario
    char name[MAX_LENGTH], location[MAX_LENGTH], schedule[MAX_LENGTH], review[MAX_LENGTH_REVIEW], username[MAX_LENGTH];
    int stars, type;
    double price;
    UserLinked* user;

    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_CONTENT, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las publicacions!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Primer usuario
        fscanf(f, "%s %d %s %s %s %d %2lf %s", name, &type, location, schedule, review, &stars, &price, username);
        first_a = make_activity_linked(name, type, location, schedule, review, stars, price, username, first_a);
        // Resto de usuarios
        while (fscanf(f, "%s %d %s %s %s %d %2lf %s", name, &type, location, schedule, review, &stars, &price, username) > 7) {//Mientras los datos coincidan.
            make_activity_linked(name, type, location, schedule, review, stars, price, username, first_a);
        }
        fclose(f); //Cerramos el fichero f
        return first_a;

    }
    return first_a; // Si ha habido algún error, devuelve NULL
}*/

save_content_at_user(UserLinked* ){


void save_content_at_user(UserLinked* first_u, ActivityLinked* first_a){
    UserLinked* actual_user;
    while (first_a != NULL){
        actual_user = search_user(first_a->activity->username, first_u);
        for (int i = 0; )
        first_u->user->content[]
    }

}*/