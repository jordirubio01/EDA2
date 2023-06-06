#ifndef LAB_0_DICTIONARY_H
#define LAB_0_DICTIONARY_H
#define MAX_LENGTH 20
#define SIZE_DICT 1000

#endif //LAB_0_DICTIONARY_H

typedef struct{
    char word[MAX_LENGTH];
    int counter;
}Word_Counter;

typedef struct{
    int size;
    Word_Counter* elements[SIZE_DICT];
    int counter;
} Dictionary;

void merge(Dictionary* dictionary, int left, int middle, int right);

void mergeSort(Dictionary* dictionary, int let, int right);

void counter_of_words(FILE* review, Dictionary* dictionary);