#include <Windows.h>
#include <stdio.h>
#include <intrin.h>

static double TimeNow()
{
    LARGE_INTEGER c, f;
    QueryPerformanceCounter(&c);
    QueryPerformanceFrequency(&f);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
}

__declspec(noinline) static void PerformDOS(unsigned long count)
{
    for (unsigned long i = 0; i < count; ++i) _mm_pause();
}

static void TimedDOS(const char* tag, unsigned long count)
{
    printf("[%s] starting %lu pauses...\n", tag, count);
    fflush(stdout);
    double t0 = TimeNow();
    PerformDOS(count);
    double t1 = TimeNow();
    printf("[%s] done, elapsed = %.3f ms  (%.2f us/pause)\n", tag, t1 - t0, (t1 - t0) * 1000.0 / (double)count);
    fflush(stdout);
}

int main()
{
    MessageBoxA(0, "Starting, Please Place Hooks", "", 0); // gives you time to place EPT hooks


    TimedDOS("Attempt 1", 10'000UL);
    TimedDOS("Attempt 2", 100'000UL);
    TimedDOS("Attempt 3", 1'000'000UL);

    MessageBoxA(0, "Ending", "", 0);
    return 0;
}