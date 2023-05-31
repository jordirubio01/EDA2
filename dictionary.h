#ifndef LAB_0_DICTIONARY_H
#define LAB_0_DICTIONARY_H
#define MAX_LENGTH 20

#endif //LAB_0_DICTIONARY_H

typedef struct{
    char key[MAX_LENGTH];
    int value;
} Element;

typedef struct{
    int size;
    Element* elements;
    int counter;
} Dictionary;

typedef struct{
    char word[100];
    int counter;
}Word_Counter;

