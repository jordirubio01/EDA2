#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#define MAX_LENGTH_REVIEW 1000
#define TRUE 1
#define FALSE 0

/**
 *
 * @param size
 * @return
 *
 * Pre: recibe un entero con el tamaño del diccionario
 * Post: devuelve un puntero de tipo Dictionary
 */
Dictionary* init_dictionary(int size){
    Dictionary* dict = malloc(sizeof(Dictionary)); // Reservamos memoria
    dict->size = size;  // El diccionario tendrá size elementos como máximo
    dict->counter = 0;  // Inicialmente el diccionario está vacío
}


/**
 *
 * @param dictionary
 * @param left
 * @param middle
 * @param right
 *
 * Pre: recibe una estructura diccionario y tres índices (el del 1r elemento, el del elemento central y el del último elemento)
 * Post: fusiona dos subarrays ordenados
 */
void merge(Dictionary* dictionary, int left, int middle, int right){
    int i, j, k;
    int x = middle - left+1;
    int y = right - middle;

    // Cremos dos subarrays temporales
    Dictionary* left_Array = (Dictionary*)malloc(x*sizeof(Dictionary)); // Reservamos memoria para el array de la 1a mitad de elementos
    Dictionary* right_Array = (Dictionary*)malloc(y*sizeof(Dictionary)); // Reservamos memoria para el array de la 2a mitad

    for (i = 0; i < x; i++){
        left_Array[i] = dictionary[left+i]; // Añadimos la 1a mitad de elementos al array de la izquierda
    }

    for (j = 0; j < y; j++){
        right_Array[j] = dictionary[middle+1+j]; // Añadimos la 2a mitad de elementos al array de la derecha
    }

    i = 0;
    j = 0;
    k = left;

    // Fusionamos los subarrays temporales en el array original
    while (i < x && j < y){
        if (left_Array[i].counter >= right_Array[j].counter){
            dictionary[k] = left_Array[i];
            i++;
        }
        else{
            dictionary[k] = right_Array[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes del subarray izquierdo, si los hay
    while (i < x){
        dictionary[k] = left_Array[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes del subarray derecho, si los hay
    while (j < y){
        dictionary[k] = right_Array[j];
        j++;
        k++;
    }

    // Finalmente liberamos la memoria de los subarrays temporales
    free(left_Array);
    free(right_Array);
}

/**
 *
 * @param dictionary
 * @param left
 * @param right
 *
 * Pre: recibe un diccionario y 2 índices (el del 1r elemento y el del último)
 * Post: ordena de mayor a menor las veces que se repiten las palabras en las publicaciones
 */
void mergeSort(Dictionary* dictionary, int left, int right){
    if (left < right){
        int middle = (left + (right-left)) / 2;
        mergeSort(dictionary, left, middle); // Ordenamos recursivamente la mitad izquierda
        mergeSort(dictionary, middle+1, right); // Ordenamos recursivamente la mitad derecha
        merge(dictionary, left, middle, right); // Fusionamos las mitades ordenadas
    }
}

/**
 *
 * @param size
 * @param review
 * @param dictionary
 *
 * Pre:
 * Post:
 */
void counter_of_words(FILE* review, Dictionary* dictionary){

    // Leemos la publicación del usuario
    char publication[MAX_LENGTH_REVIEW];
    fgets(publication, sizeof(publication), review);

    // Separamos las palabras de la publicación
    char delimiters[] = " ,:;.¿?¡!";
    char* word = strtok(publication, delimiters);
    while(word != NULL) {
        // Eliminamos el salto de línea del final de la palabra
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }

        // Buscamos si la palabra ya está en el diccionario
        int word_found = FALSE;
        for (int idx = 0; idx < dictionary->size; idx++) {
            if (strcmp(dictionary->elements[idx]->word, word) == 0) {
                // Si la palabra ya está en el diccionario, incrementamos su contador
                dictionary->elements[idx]->counter++;
                word_found = TRUE;
                break;
            }
        }

        // Si la palabra no está en el diccionario, la añadimos con el contador en 1
        if (word_found == FALSE){
            strcpy(dictionary->elements[dictionary->size]->word, word);
            dictionary->elements[dictionary->size]->counter = 1;
            dictionary->size++;
        }

        // Obtenemos la siguiente palabra de la publicación
        word = strtok(NULL, " ");
    }

    // Ordenamos el diccionario de mayor a menor uso utilizando mergesort
    mergeSort(dictionary, 0, dictionary->size - 1);

    printf("\nLas 10 palabras con mayor uso son;\n");
    for (int idx = 0; idx < dictionary->size && idx < 10; idx++){
        printf("%s: %d veces\n", dictionary->elements[idx]->word, dictionary->elements[idx]->counter);
    }
}


