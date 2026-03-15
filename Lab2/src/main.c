#include "main.h"

int read_samples(char *filename, MyStructure **samples)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        return -1;
    }

    int expected_len = 0;
    if (fscanf(file, "%d ", &expected_len) != 1)
    {
        fclose(file);
        return -2;
    }

    *samples = (MyStructure *)malloc(expected_len * sizeof(MyStructure));
    if (*samples == NULL)
    {
        fclose(file);
        return -3;
    }

    char *key = NULL, *value = NULL;
    size_t key_len = 0, value_len = 0;
    ssize_t key_read, value_read;
    int i;
    for (i = 0; i < expected_len; i++)
    {
        key_read = getline(&key, &key_len, file);
        if (key_read == -1)
            break;
        if (key[key_read - 1] == '\n')
            key[key_read - 1] = '\0';

        value_read = getline(&value, &value_len, file);
        if (value_read == -1)
            break;
        if (value[value_read - 1] == '\n')
            value[value_read - 1] = '\0';

        (*samples)[i].key = strdup(key);
        (*samples)[i].value = strdup(value);
    }
    free(key);
    free(value);

    fclose(file);
    if (i < expected_len)
    {
        MyStructure *new_samples = (MyStructure *)realloc(*samples, i * sizeof(MyStructure));
        if (!new_samples && i > 0)
        {
            free(*samples);
            return -4;
        }
        *samples = new_samples;
    }
    return i;
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

    return left;
}
int find_by_key(MyStructure *samples, int len, char *key)
{
    int pos = binary_search_insert(samples, len, key);
    if (pos < len && strcmp(samples[pos].key, key) == 0)
        return pos;
    else
        return -1;
}
int insertion_sort(MyStructure *samples, int len)
{
    for (int i = 1; i < len; i++)
    {
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

    char *key1 = malloc(1024);
    char *key2 = malloc(1024);
    char *key3 = malloc(1024);
    if (!key1 || !key2 || !key3)
    {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return;
    }
    printf("Enter three keys to find:\n");
    scanf("%s %s %s", key1, key2, key3);

    int pos1 = find_by_key(samples, len_samples, key1);
    int pos2 = find_by_key(samples, len_samples, key2);
    int pos3 = find_by_key(samples, len_samples, key3);
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
    demonstration("data_samples/random_samples.txt");
    demonstration("data_samples/sorted_samples.txt");
    demonstration("data_samples/reversed_samples.txt");
    return 0;
}
#endif