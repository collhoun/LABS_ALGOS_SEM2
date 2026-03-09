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

int main()
{
    test_empty_array();
    test_one_element();
    test_random_array();
    test_reverse_array();
    test_sorted_array();
    return 0;
}