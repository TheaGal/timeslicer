#pragma once

#include <chrono>


namespace THEA
{
namespace timeslicer
{

void performance_report_init();
void print_performance_report();

using high_res_time_t = std::chrono::high_resolution_clock::time_point;
using high_res_duration_t = std::chrono::high_resolution_clock::duration;

class Performance_timer
{
public:
    Performance_timer(char const* func_name);
    ~Performance_timer();

private:
    char const* m_func_name;
    high_res_time_t m_start_time;
};

} // namespace timeslicer
} // namespace THEA
