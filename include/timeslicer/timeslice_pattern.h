#pragma once

#include "timeslicer.h"  // for Slice_pattern


namespace THEA
{
namespace timeslicer
{

/// @details This is meant to be called from the macro TIMESLICER_SCOPED.
void log_timeslice_pattern(char const* func_name, Slice_pattern slice_pattern);

} // namespace timeslicer
} // namespace THEA
