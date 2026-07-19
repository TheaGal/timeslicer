#include "timeslicer/timeslice_pattern.h"
#include "timeslicer/timeslicer.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <unordered_map>


namespace
{

using namespace THEA::timeslicer;

struct Slice_pattern_with_offset
{
    Slice_pattern slice_pattern;
    uint8_t sub_idx;
};

std::unordered_map<char const*, Slice_pattern_with_offset> g_func_slice_patterns;

} // namespace


namespace THEA
{

void timeslicer::timeslice_pattern_report_init()
{
    g_func_slice_patterns.clear();
}

void timeslicer::print_timeslice_pattern_report()
{
    constexpr int32_t k_column_width{ 30 };
    std::cout << std::left << std::setw(k_column_width) << "| FUNCTION_NAME"
              << "|01234 56789 10    15    20    25    30    35    40    45    50    55    60  |\n"
              << "|" << std::right << std::setfill('-') << std::setw(k_column_width) << "|"
              << std::setfill('-') << std::setw(64 + 14) << "|\n";
    std::cout << std::setfill(' ');

    for (auto const& [func_name, slice_pattern] : g_func_slice_patterns)
    {
        std::cout << std::left << std::setw(k_column_width) << (std::string("| ") + func_name)
                  << "|";

        for (uint8_t i = 0; i < 64; i++)
        {
            std::cout << (eval_tick_valid_timeslice_at_tick(slice_pattern.slice_pattern,
                                                            slice_pattern.sub_idx,
                                                            i)
                              ? "*"
                              : " ");

            if ((i + 1) % 5 == 0)
                std::cout << " ";
        }

        std::cout << "|\n";
    }
}


void timeslicer::log_timeslice_pattern(char const* func_name,
                                       Slice_pattern slice_pattern,
                                       uint8_t sub_idx)
{
    if (g_func_slice_patterns.find(func_name) != g_func_slice_patterns.end())
        throw std::runtime_error("Inserting slice pattern for already registered func name!!");

    g_func_slice_patterns[func_name] = {
        .slice_pattern = slice_pattern,
        .sub_idx = sub_idx,
    };
}

} // namespace THEA
