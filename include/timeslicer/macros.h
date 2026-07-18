#pragma once

#include "performance_timer.h"
#include "timeslice_pattern.h"
#include "timeslicer.h"

#include <mutex>


#define TIMESLICER_INIT THEA::timeslicer::init()

#define TIMESLICER_TICK THEA::timeslicer::tick()


#define TIMESLICER_SCOPED(slice_pattern, sub_idx)                                                  \
    static std::once_flag __timeslicer_scoped_call_once_flag;                                      \
    std::call_once(__timeslicer_scoped_call_once_flag, []() {                                      \
        THEA::timeslicer::log_timeslice_pattern(__func__,                                          \
                                                THEA::timeslicer::Slice_pattern::slice_pattern);   \
    });                                                                                            \
                                                                                                   \
    if (!THEA::timeslicer::eval_tick_valid_timeslice(                                              \
            THEA::timeslicer::Slice_pattern::slice_pattern,                                        \
            sub_idx))                                                                              \
    {                                                                                              \
        return;                                                                                    \
    }                                                                                              \
                                                                                                   \
    THEA::timeslicer::Performance_timer(__func__)


#define TIMESLICER_PRINT_PERFORMANCE_REPORT THEA::timeslicer::print_performance_report()