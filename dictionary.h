#ifndef LAB_0_DICTIONARY_H
#define LAB_0_DICTIONARY_H
#define MAX_LENGTH 25
#define SIZE_DICT 1000

#endif //LAB_0_DICTIONARY_H

/// Estructura de palabra
typedef struct{
    char word[MAX_LENGTH];
    int counter;
}Word_Counter;

/// Estructura de diccionario
typedef struct{
    int size;
    Word_Counter* elements[SIZE_DICT];
    int counter;
} Dictionary;

/// Funciones diccionario
Dictionary* init_dictionary(int size);

void counter_of_words(Dictionary* dictionary);

/// Funciones de ordenación

void merge(Dictionary* dictionary, int left, int middle, int right);

void mergeSort(Dictionary* dictionary, int left, int right);