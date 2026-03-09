#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStructure
{
    const char *key;
    const char *value;
} MyStructure;

int read_samples(const char *filename, MyStructure **samples);
int binary_search_insert(MyStructure *samples, int len, const char *key);
int insertion_sort(MyStructure *samples, int len);
void demonstration(const char *filename);
#endif