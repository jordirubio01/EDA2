#include "content.h"
#ifndef LAB_0_DICTIONARY_H
#define LAB_0_DICTIONARY_H
#define MAX_LENGTH 25
#define SIZE_DICT 1000

#endif //LAB_0_DICTIONARY_H

/// Estructura de palabra
typedef struct{
    char word[MAX_LENGTH];
    int repetitions;
}Word_Counter;

/// Estructura de diccionario
typedef struct{
    int size;
    Word_Counter* elements;
    int counter;
} Dictionary;

/// Funciones diccionario
Dictionary* init_dictionary();

void realloc_dictionary(Dictionary* dictionary);

int search_by_value(Dictionary* dictionary, char word[MAX_LENGTH]);

void add_value(Dictionary* dictionary, char word[MAX_LENGTH]);

void modify_value(Dictionary* dictionary, char word[MAX_LENGTH]);

void manage_words_from_dictionary(Dictionary* dictionary, char text[MAX_LENGTH]);

void load_dictionary(Dictionary* dictionary, ActivityLinked* activity);

void most_used_words(Dictionary* dictionary);

/// Funciones de ordenación
void insertionSort(Dictionary* dictionary);