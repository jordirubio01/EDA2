#include <malloc.h>
#include "content.h"


/******** FUNCIONES INTERNAS ********/
/**
 *
 * @return
 *
 * Pre: -
 * Post: Lista dinámica con todas las actividades creada; devuelve un puntero a la primera actividad del usuario
 */
ActivityLinked* init_activity_list(UserLinked* u) {
    ActivityLinked *first_a; // Primer usuario
    // Datos de cada usuario
    char name[MAX_LENGTH], location[MAX_LENGTH], schedule[MAX_LENGTH], review[MAX_LENGTH_REVIEW], username[MAX_LENGTH];
    int stars, type;
    float price;

    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_CONTENT, "r"); //Abrimos el fichero input en modo read
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("%cError al recuperar las publicacions!\n", 173); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Primer usuario
        fscanf(f, "%s %d %s %s %d %f %s", name, &type, location, schedule, &stars, &price, username);
        fgetc(f); // Ignoramos el carácter '\n'
        fgets(review, MAX_LENGTH_REVIEW, f);
        first_a = make_activity_linked(name, type, location, schedule, review, stars, price, username, NULL, u);
        // Resto de usuarios
        while (fscanf(f, "%s %d %s %s %d %f %s", name, &type, location, schedule, &stars, &price, username) > 6) { //Mientras los datos coincidan.
            fgetc(f); // Ignoramos el carácter '\n'
            fgets(review, MAX_LENGTH_REVIEW, f);
            make_activity_linked(name, type, location, schedule, review, stars, price, username, first_a, u);
        }
        fclose(f); //Cerramos el fichero f
        return first_a;
    }
    return NULL; // Si ha habido algún error, devuelve NULL
}

/******** FUNCIONES PRINCIPALES ********/
/**
 *
 * @param first
 * @param user
 * @return
 *
 * Pre: recibe un puntero a la primera actividad y un puntero al usuario
 * Post: una nueva actividad ha sido publicada
 */
Activity* new_content(ActivityLinked* first, User* user, UserLinked* u){
    char name[MAX_LENGTH], location[MAX_LENGTH], schedule[MAX_LENGTH], review[MAX_LENGTH_REVIEW];
    int stars, type;
    float price;

    printf("%s\nRellena la siguiente ficha t%ccnica\n", BARS, 130);
    printf("Nombre:\n");
    scanf("%s", name);
    printf("Localidad:\n");
    scanf("%s", location);
    printf("Horario [hh:mm-hh:mm]:\n");
    scanf("%s", schedule);
    printf("Precio:\n");
    scanf("%f", &price);
    printf("%s", BARS);
    printf("\n1-Ciencia\n2-Gastronomia\n3-Cultura\n4-Deportes\n5-Musica\n%s\n%cmbito [Introduce numero]:\n", BARS, 181);
    scanf("%d", &type);
    printf("Opinion:\n");
    fgetc(stdin);
    fgets(review, MAX_LENGTH_REVIEW, stdin);
    printf("Valoraci%cn [Estrellas (1-5)]:\n", 162);
    scanf("%d", &stars);
    printf("%s", BARS);

    ActivityLinked* new_activity = make_activity_linked(name, type, location, schedule, review, stars, price, user->username, first, u);
    save_activity(new_activity->activity);
    return new_activity->activity;
}

/**
 *
 * @param name
 * @param type
 * @param location
 * @param schedule
 * @param review
 * @param stars
 * @param price
 * @param username
 * @param first
 * @return
 *
 * Pre:
 * Post:
 */
ActivityLinked* make_activity_linked(char name[MAX_LENGTH], int type, char location[MAX_LENGTH], char schedule[MAX_LENGTH],
                                     char review[MAX_LENGTH_REVIEW], int stars, float price, char username[MAX_LENGTH], ActivityLinked* first, UserLinked* u){
    ActivityLinked* c = (ActivityLinked*) malloc(sizeof(ActivityLinked)); // Reservamos memoria para ActivityLinked
    c->activity = (Activity*) malloc(sizeof(Activity)); // Reservamos memoria para Activity
    strcpy(c->activity->name, name);
    strcpy(c->activity->location, location);
    strcpy(c->activity->schedule, schedule);
    strcpy(c->activity->review, review);
    strcpy(c->activity->username, username);
    c->activity->stars = stars;
    c->activity->type = type;
    c->activity->price = price;
    c->next = NULL;
    if (first != NULL){
        ActivityLinked* last = get_last_activity(first);
        last->next = c;
    }
    save_content_at_user(u, c);
    return c;
}

/**
 *
 * @param activity
 * @return
 *
 * Pre: recibe un puntero a una actividad
 * Post:
 */
int save_activity(Activity* activity){
    // Abrimos el fichero de usuarios
    int f1 = SUCCESS, exit = 0;
    FILE *f = fopen(FILE_CONTENT, "a"); //Abrimos el fichero de usuarios en modo append (añadiremos una línea)
    if (f == NULL) f1 = FILE_NOT_FOUND; //Si el archivo es NULL, mandamos un error
    if (f1 == FILE_NOT_FOUND)
        printf("Error al recuperar las actividades registradas!\n"); //Si fa es NULL, mostramos un mensaje de aviso
    if (f1 == SUCCESS) { //Si el fichero ha sido abierto de forma exitosa...
        // Resto de usuarios
        fprintf(f, "\n%s %d %s %s %d %f %s\n", activity->name, activity->type, activity->location, activity->schedule, activity->stars, activity->price, activity->username);
        fputs(activity->review, f);
        fclose(f); //Cerramos el fichero f
        return SUCCESS;
    }
    return FILE_NOT_FOUND; // Si ha habido algún error, lo retorna
}

/**
 *
 * @param first_u
 * @param first_a
 *
 * Pre:
 * Post:
 */
void save_content_at_user(UserLinked* first_u, ActivityLinked* received_a){
    UserLinked* current_user = search_user(received_a->activity->username, first_u);
    ActivityLinked* a = (ActivityLinked*) malloc(sizeof(ActivityLinked));
    a->activity = (Activity*) malloc(sizeof(Activity));
    a->activity = received_a->activity;
    a->next = NULL;
    // Si el usuario aún no tiene publicaciones...
    if (current_user->user->content == NULL) current_user->user->content = a; // La nueva publicación es la primera (y última)
    // Si el usuario ya ha publicado antes...
    else{
        ActivityLinked* last = get_last_activity(current_user->user->content); // La nueva publicación es la última
        last->next = a;
    }
}


/**
 *
 * @param activity
 *
 * Pre:
 * Post:
 */
void print_content(Activity* activity){
    printf("%s", BARS);
    printf("\t\t\t\t\t\t\t\t%c%s%c", 34, activity->name, 34);
    printf("\n%s", BARS);
    printf("\nUsuario: %s", activity->username);
    printf("\n%cmbito: %s", 181, get_type(activity->type));
    printf("\nLocalidad: %s", activity->location);
    printf("\nHorario: %s h", activity->schedule);
    printf("\nPrecio:\t%.2f (euros)", activity->price);
    printf("\nValoraci%cn [0-5]:", 162);
    for (int i = 0; i < activity->stars; i++){
        printf("%c",3);
    }
    printf("\nRese%ca: %s", 164, activity->review);
    printf("\n%s\n", BARS);
}

/**
 *
 * @param a
 *
 * Pre:
 * Post:
 */
void print_all_publications(ActivityLinked* a){
    ActivityLinked* temp = a;
    while (temp != NULL){
        print_content(temp->activity);
        temp = temp->next;
    }
}

/******** FUNCIONES AUXILIARES (implementadas en varias funciones) ********/
/**
 *
 * @param first
 * @return
 *
 * Pre: recibe un puntero a la primera actividad
 * Post: devuelve un puntero a la última actividad del usuario
 */
ActivityLinked* get_last_activity(ActivityLinked* first){
    ActivityLinked* temp = first;
    while (temp->next != NULL){
        temp = temp->next;
    }
    return temp;
}

/**
 *
 * @param num
 * @return
 *
 * Pre:
 * Post:
 */
const char* get_type(int num){
    if(num == 1) return "Ciencia";
    else if(num == 2) return "Gastronomia";
    else if(num == 3) return "Cultura";
    else if(num == 4) return "Deporte";
    else if(num == 5) return "Musica";
    return NULL;
}