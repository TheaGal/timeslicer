#include "timeslicer/performance_timer.h"

#include <iostream>
#include <map>
#include <sstream>
#include <unordered_map>
#include <vector>


namespace
{

using namespace THEA::timeslicer;

struct Perf_report
{
    std::vector<high_res_duration_t> duration_samples;
};

std::unordered_map<char const*, Perf_report> g_per_func_perf_report_map;

} // namespace


namespace THEA
{

void timeslicer::performance_report_init()
{
    g_per_func_perf_report_map.clear();
}

void timeslicer::print_performance_report()
{
    // Sort into total time, descending.
    std::map<int64_t, std::vector<std::string>> ordered_report_strs;

    for (auto const& [func_name, report] : g_per_func_perf_report_map)
    {
        // Calc report statistics.
        high_res_duration_t total_dur{ 0 };
        for (auto dur : report.duration_samples)
            total_dur += dur;
        high_res_duration_t avg_dur{ total_dur / report.duration_samples.size() };

        // Form into report string.
        std::ostringstream oss;
        oss << func_name << "()\tavg=" << avg_dur << ",\tsamples=" << report.duration_samples.size()
            << ",\ttotal=" << total_dur << "\n";

        ordered_report_strs[-total_dur.count()].emplace_back(oss.str());
    }

    // Print.
    for (auto const& [_, report_strs] : ordered_report_strs)
    for (auto const& report_str : report_strs)
        std::cout << report_str;
}

namespace timeslicer
{

Performance_timer::Performance_timer(char const* func_name)
    : m_func_name(func_name)
    , m_start_time(std::chrono::high_resolution_clock::now())
{
}

Performance_timer::~Performance_timer()
{
    high_res_time_t time_now{ std::chrono::high_resolution_clock::now() };

    high_res_duration_t delta_time{ time_now - m_start_time };

    // Incorporate into report statistics.
    auto& report = g_per_func_perf_report_map[m_func_name];
    report.duration_samples.emplace_back(delta_time);
}

} // namespace timeslicer
} // namespace THEA
