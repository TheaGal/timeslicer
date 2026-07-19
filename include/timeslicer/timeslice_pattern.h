#pragma once

#include "timeslicer.h"  // for Slice_pattern


namespace THEA
{
namespace timeslicer
{

void timeslice_pattern_report_init();
void print_timeslice_pattern_report();

/// Logs the pattern of a timesliced function. Must be called only once.
/// @details This is meant to be called from the macro TIMESLICER_SCOPED.
void log_timeslice_pattern(char const* func_name, Slice_pattern slice_pattern, uint8_t sub_idx);

} // namespace timeslicer
} // namespace THEA
