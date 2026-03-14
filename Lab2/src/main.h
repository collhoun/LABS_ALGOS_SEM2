#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStructure
{
    char *key;
    char *value;
} MyStructure;

int read_samples(char *filename, MyStructure **samples);
int binary_search_insert(MyStructure *samples, int len, char *key);
int insertion_sort(MyStructure *samples, int len);
void demonstration(char *filename);
#endif