#include "timeslicer_public.h"

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>


void some_func()
{
    TIMESLICER_SCOPED(ONES, 0);
    std::cout << __func__ << "()\n";
}

void some_func2()
{
    TIMESLICER_SCOPED(TWOS, 0);
    std::cout << __func__ << "()\n";
}

void some_func3()
{
    TIMESLICER_SCOPED(TWOS, 1);
    std::cout << __func__ << "()\n";
}

void some_func4()
{
    TIMESLICER_SCOPED(EIGHTS, 3);
    std::cout << __func__ << "()\n";
}


int32_t main()
{
    TIMESLICER_INIT;

    for (size_t i = 0; i < 500; i++)
    {
        TIMESLICER_TICK;
        std::cout << "--------------- Tick " << i << " ---------------\n";

        some_func();
        some_func2();
        some_func3();
        some_func4();
    }

    std::cout << "-=-=-=-=-=-=-=- FINISH -=-=-=-=-=-=-=-\n";

    TIMESLICER_PRINT_PERFORMANCE_REPORT;

    return 0;
}
