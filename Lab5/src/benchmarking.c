#define REPEAT 50
#define WARMUP 3
#include <windows.h>

double benchmark(double (*func)(void *), void *arg)
{
    LARGE_INTEGER frequency, start, end;

    QueryPerformanceFrequency(&frequency);

    // прогрев для кэша
    for (int i = 0; i < WARMUP; i++)
        func(arg);

    double total = 0.0;
    for (int i = 0; i < REPEAT; i++)
    {
        QueryPerformanceCounter(&start);

        func(arg);

        QueryPerformanceCounter(&end);

        double elapsed = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        total += elapsed;
    }
    return total / REPEAT;
}