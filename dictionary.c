#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <malloc.h>
#define MAX_LENGTH_REVIEW 1000

//FUNCIONES AUXILIARES
/*
void create_dictionary(int size){
    Dictionary* dictionary;
    dictionary = (Dictionary*) malloc(sizeof (Dictionary));
    dictionary->size = size;
    dictionary->counter = 0;
    dictionary->elements[0] = *(Element *) calloc(dictionary->size, sizeof(Element *));
    for(int idx = 0; idx < dictionary->size; idx++){
        dictionary->elements[idx] = NULL;
    }
}

void add_element_as_first(Dictionary* dictionary, char key, int value){
    Element *element = (Element*) malloc(sizeof (Element));
}


void counter_of_words(int size, FILE* review){
    Word_Counter dictionary[size];
    int dictionary_size = 0;
    char publication[MAX_LENGTH_REVIEW];
    fgets(publication, sizeof(publication), review);

    separadores[] = " ,.?¿¡!;:";
    char* word = strtok_r(publication, separadores)
    while(word != NULL){
        if(word[strlen(word)-1] == '\n'){
            token[strlen(token)-1] = '\0';
        }

        int word_found = FALSE;
        while(word_found == FALSE){
            for(int idx = 0; idx < dictionary_size; idx++){
                if(strcmp(dictionary[idx].word, word) == 0){
                    dictionary[idx].counter++;
                    word_found = TRUE;
                }
            }
        }

        if (
    }
}*/