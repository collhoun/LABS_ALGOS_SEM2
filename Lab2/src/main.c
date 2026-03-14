#include "main.h"
// поправить const char на char
// сделать так, чтобы я мог читать строки произвольной длины (например делать realloc)
// плюс два теста
// лучше считывать не через fscanf
// поправить текстовый файл с хранением информации
int read_samples(char *filename, MyStructure **samples)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return -1;
    }

    int len_samples;
    if (fscanf(file, "%d", &len_samples) != 1)
    {
        fclose(file);
        return -2;
    }

    *samples = (MyStructure *)malloc(len_samples * sizeof(MyStructure));
    if (*samples == NULL)
    {
        fclose(file);
        return -3;
    }

    char key_buffer[1024];
    char value_buffer[1024];

    for (int i = 0; i < len_samples; i++)
    {
        if (fscanf(file, "%s %s", key_buffer, value_buffer) != 2)
        {
            // нужна ли здесь проверка на память?
            free(*samples);
            fclose(file);
            return -4;
        }

        (*samples)[i].key = strdup(key_buffer);
        (*samples)[i].value = strdup(value_buffer);
    }

    fclose(file);
    return len_samples;
}

int binary_search_insert(MyStructure *samples, int len, char *key)
{
    int left = 0, right = len;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (strcmp(samples[mid].key, key) < 0)
            left = mid + 1;
        else
            right = mid;
    }

    // if (left < len && strcmp(samples[left].key, key) != 0)
    //     return -1;
    return left;
}
int insertion_sort(MyStructure *samples, int len)
{
    for (int i = 1; i < len; i++)
    {
        // проверить почему samples битый
        MyStructure tmp = samples[i];
        int pos = binary_search_insert(samples, i, tmp.key);

        for (int j = i; j > pos; j--)
        {
            samples[j] = samples[j - 1];
        }
        samples[pos] = tmp;
    }
    return 1;
}

void demonstration(char *filename)
{
    MyStructure *samples;
    int len_samples = read_samples(filename, &samples);
    printf("------------------------------\n");
    printf("Before sort:\n");
    for (int i = 0; i < len_samples; i++)
    {
        printf("%s %s\n", samples[i].key, samples[i].value);
    }
    insertion_sort(samples, len_samples);
    printf("------------------------------\n");
    printf("After sort:\n");
    for (int i = 0; i < len_samples; i++)
    {
        printf("%s %s\n", samples[i].key, samples[i].value);
    }

    const char *key1 = malloc(1024);
    const char *key2 = malloc(1024);
    const char *key3 = malloc(1024);
    if (!key1 || !key2 || !key3)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }
    printf("Enter three keys to find:\n");
    scanf("%s %s %s", key1, key2, key3);

    int pos1 = binary_search_insert(samples, len_samples, key1);
    int pos2 = binary_search_insert(samples, len_samples, key2);
    int pos3 = binary_search_insert(samples, len_samples, key3);
    if (pos1 >= 0)
    {
        printf("%s %s\n", samples[pos1].key, samples[pos1].value);
    }
    if (pos2 >= 0)
    {
        printf("%s %s\n", samples[pos2].key, samples[pos2].value);
    }
    if (pos3 >= 0)
    {
        printf("%s %s\n", samples[pos3].key, samples[pos3].value);
    }

    free(samples);
    free((void *)key1);
    free((void *)key2);
    free((void *)key3);
}

#ifndef TEST
int main()
{
    demonstration("C:/Users/Huawei/C_programming/Labs_algos/Lab2/data_samples/random_samples.txt");
    demonstration("C:/Users/Huawei/C_programming/Labs_algos/Lab2/data_samples/sorted_samples.txt");
    demonstration("C:/Users/Huawei/C_programming/Labs_algos/Lab2/data_samples/reversed_samples.txt");
    return 0;
}
#endif