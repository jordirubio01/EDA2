#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define MAX_LENGTH_REVIEW 500
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define FILE_NOT_FOUND (-2)
#define FILE_CONTENT "resources/content.txt"

/**
 *
 * @param size
 * @return
 *
 * Pre: -
 * Post: devuelve un puntero de tipo Dictionary
 */
Dictionary* init_dictionary(){
    Dictionary* dict = (Dictionary*) malloc(sizeof(Dictionary)); // Reservamos memoria para el diccionario
    dict->size = SIZE_DICT;  // El diccionario tendrá size elementos como máximo
    dict->counter = 0;  // Inicialmente el diccionario está vacío
    dict->elements = (Word_Counter*) malloc(sizeof(Word_Counter) * SIZE_DICT);
    for (int i = 0; i < SIZE_DICT; i++){
        dict->elements[i].repetitions = 0;
    }
    return dict;
}

void realloc_dictionary(Dictionary* dictionary){
    dictionary->elements = realloc(dictionary, sizeof(Dictionary) * SIZE_DICT);
    dictionary->size += dictionary->size;
}

int search_by_value(Dictionary* dictionary, char word[MAX_LENGTH]){
    for (int i = 0; i < SIZE_DICT; i++){
        if (strcmp(dictionary->elements[i].word, word) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

void add_value(Dictionary* dictionary, char word[MAX_LENGTH]){
    if (dictionary->counter < dictionary->size){
        strcpy(dictionary->elements[dictionary->counter].word, word);
        dictionary->elements[dictionary->counter].repetitions = 1;
    }
    else{
        realloc_dictionary(dictionary);
        strcpy(dictionary->elements[dictionary->counter].word, word);
        dictionary->elements[dictionary->counter].repetitions = 1;
    }
    dictionary->counter++;
}

void modify_value(Dictionary* dictionary, char word[MAX_LENGTH]){
    for (int i = 0; i < SIZE_DICT; i++){
        if (strcmp(dictionary->elements[i].word, word) == 0){
            dictionary->elements[i].repetitions++;
        }
    }
}

void manage_words_from_dictionary(Dictionary* dictionary, char text[MAX_LENGTH]){
    int election;
    char delimiters[] = " ,.;:-¡!¿?";
    char* word = strtok(text, delimiters);
    election = search_by_value(dictionary, word);
    if (election == TRUE){
        modify_value(dictionary, word);
    }
    else add_value(dictionary, word);
    while (word != NULL){
        word = strtok(NULL, delimiters);
        if (word != NULL){
            election = search_by_value(dictionary, word);
            if (election == TRUE){
                modify_value(dictionary, word);
            }
            else add_value(dictionary, word);
        }
    }
}


void load_dictionary(Dictionary* dictionary, ActivityLinked* activity){
    ActivityLinked* temp = activity;
    while (temp != NULL){
        manage_words_from_dictionary(dictionary, temp->activity->review);
        temp = temp->next;
    }
}


void most_used_words(Dictionary* dictionary){
    insertionSort(dictionary);
    printf("Las 10 palabras m%cs usadas son:\n", 160);
    for (int i = dictionary->counter-2; i > dictionary->counter-11; i--){
        printf("%s: %d repeticiones\n", dictionary->elements[i].word, dictionary->elements[i].repetitions);
    }
}

/******** FUNCIONES DE ORDENACIÓN ********/
void insertionSort(Dictionary* dictionary){
    int i, j;
    Word_Counter temp;
    for (i = 0; i < dictionary->counter; i++){
        j = i;
        while (j >= 0 && dictionary->elements[j-1].repetitions > dictionary->elements[j].repetitions){
            temp = dictionary->elements[j - 1];
            dictionary->elements[j - 1] = dictionary->elements[j];
            dictionary->elements[j] = temp;
            j--;
        }
    }
}