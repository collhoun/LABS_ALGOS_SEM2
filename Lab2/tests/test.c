#define TEST
#include <assert.h>
#include "../src/main.h"

void test_empty_array()
{
    // проверка на пусткой массив
    MyStructure *samples = NULL;
    insertion_sort(samples, 0);
    assert(samples == NULL);
    free(samples);
}

void test_one_element()
{
    // проверка на один элемент
    MyStructure *samples = (MyStructure *)malloc(sizeof(MyStructure));
    samples[0].key = "key1";
    samples[0].value = "value1";
    insertion_sort(samples, 1);
    assert(strcmp(samples[0].key, "key1") == 0);
    assert(strcmp(samples[0].value, "value1") == 0);
    free(samples);
}

void test_random_array()
{
    // случайный массив
    MyStructure *samples;
    MyStructure *samples_sorted;
    int len_sorted_samples = read_samples("tests_data/sorted_samples.txt", &samples_sorted);
    int len_samples = read_samples("tests_data/random_samples.txt", &samples);
    insertion_sort(samples, len_samples);
    for (int i = 0; i < len_samples; i++)
    {
        assert(strcmp(samples[i].key, samples_sorted[i].key) == 0);
        assert(strcmp(samples[i].value, samples_sorted[i].value) == 0);
    }
    free(samples);
}

void test_reverse_array()
{
    // перевернутый массив
    MyStructure *samples;
    MyStructure *samples_sorted;
    int len_sorted_samples = read_samples("tests_data/sorted_samples.txt", &samples_sorted);
    int len_samples = read_samples("tests_data/reversed_samples.txt", &samples);
    insertion_sort(samples, len_samples);
    for (int i = 0; i < len_samples; i++)
    {
        assert(strcmp(samples[i].key, samples_sorted[i].key) == 0);
        assert(strcmp(samples[i].value, samples_sorted[i].value) == 0);
    }
    free(samples);
}

void test_sorted_array()
{
    // отсортированный массив
    MyStructure *samples;
    MyStructure *samples_sorted;
    int len_sorted_samples = read_samples("tests_data/sorted_samples.txt", &samples_sorted);
    int len_samples = read_samples("tests_data/sorted_samples.txt", &samples);
    insertion_sort(samples, len_samples);
    for (int i = 0; i < len_samples; i++)
    {
        assert(strcmp(samples[i].key, samples_sorted[i].key) == 0);
        assert(strcmp(samples[i].value, samples_sorted[i].value) == 0);
    }
    free(samples);
}

void test_duplicate_keys()
{
    // массив с одинаковыми ключами
    MyStructure *samples = (MyStructure *)malloc(5 * sizeof(MyStructure));
    samples[0].key = "key1";
    samples[0].value = "value1";
    samples[1].key = "key1";
    samples[1].value = "value2";
    samples[2].key = "key1";
    samples[2].value = "value3";
    samples[3].key = "key2";
    samples[3].value = "value4";
    samples[4].key = "key2";
    samples[4].value = "value5";
    insertion_sort(samples, 5);
    assert(strcmp(samples[0].key, "key1") == 0);
    assert(strcmp(samples[1].key, "key1") == 0);
    assert(strcmp(samples[2].key, "key1") == 0);
    assert(strcmp(samples[3].key, "key2") == 0);
    assert(strcmp(samples[4].key, "key2") == 0);

    free(samples);
}

void test_large_random_array()
{
    int size = 1000;
    MyStructure *samples = malloc(size * sizeof(MyStructure));
    assert(samples != NULL);

    char key_buffer[20], value_buffer[20];
    for (int i = 0; i < size; i++)
    {
        samples[i].key = strdup(key_buffer);
        samples[i].value = strdup(value_buffer);
        assert(samples[i].key != NULL && samples[i].value != NULL);
    }

    insertion_sort(samples, size);

    for (int i = 0; i < size - 1; i++)
    {
        assert(strcmp(samples[i].key, samples[i + 1].key) <= 0);
    }

    for (int i = 0; i < size; i++)
    {
        free(samples[i].key);
        free(samples[i].value);
    }
    free(samples);
}
int main()
{
    test_empty_array();
    test_one_element();
    test_random_array();
    test_reverse_array();
    test_sorted_array();
    test_duplicate_keys();
    test_large_random_array();
    return 0;
}