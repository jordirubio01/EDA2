#include <stdio.h>
#include "dictionary.h"
#include <malloc.h>

//FUNCIONES AUXILIARES
/*
void create_dictionary(int size){
    Dictionary* dictionary;
    dictionary = (Dictionary*) malloc(sizeof (Dictionary));
    dictionary->size = size;
    dictionary->counter = 0;
    dictionary->elements[0] = (Element *) calloc(dictionary->size, sizeof(Element *));
    for(int idx = 0; idx < dictionary->size; idx++){
        dictionary->elements[idx] = NULL;
    }
}

void add_element_as_first(Dictionary* dictionary, char key, int value){
    Element *element = (Element*) malloc(sizeof (Element));
}
 */