#pragma once

#include "performance_timer.h"
#include "timeslicer.h"


#define TIMESLICER_INIT THEA::timeslicer::init()

#define TIMESLICER_TICK THEA::timeslicer::tick()

#define TIMESLICER_SCOPED(slice_pattern, sub_idx)                                                  \
    if (!THEA::timeslicer::eval_tick_valid_timeslice(                                              \
            THEA::timeslicer::Slice_pattern::slice_pattern,                                        \
            sub_idx))                                                                              \
    {                                                                                              \
        return;                                                                                    \
    }                                                                                              \
    THEA::timeslicer::Performance_timer(__func__)

#define TIMESLICER_PRINT_PERFORMANCE_REPORT THEA::timeslicer::print_performance_report()