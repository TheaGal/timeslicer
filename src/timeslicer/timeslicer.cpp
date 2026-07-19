#include "timeslicer/timeslicer.h"

#include "timeslicer/performance_timer.h"
#include "timeslicer/timeslice_pattern.h"

#include <cstdint>
#include <stdexcept>


namespace
{

uint8_t g_tick_counter{ 0 };

} // namespace


namespace THEA
{

void timeslicer::init()
{
    g_tick_counter = 0;
    performance_report_init();
    timeslice_pattern_report_init();
}

void timeslicer::tick()
{
    g_tick_counter++;
}

bool timeslicer::eval_tick_valid_timeslice(Slice_pattern slice_pattern, uint8_t sub_idx)
{
    return eval_tick_valid_timeslice_at_tick(slice_pattern, sub_idx, g_tick_counter);
}

bool timeslicer::eval_tick_valid_timeslice_at_tick(Slice_pattern slice_pattern,
                                                   uint8_t sub_idx,
                                                   uint8_t tick)
{
    switch (slice_pattern)
    {
        case Slice_pattern::ONES:
            return true;

        case Slice_pattern::TWOS:
            return ((tick & static_cast<uint8_t>(0b0000'0001)) == sub_idx);

        case Slice_pattern::FOURS:
            return ((tick & static_cast<uint8_t>(0b0000'0011)) == sub_idx);

        case Slice_pattern::EIGHTS:
            return ((tick & static_cast<uint8_t>(0b0000'0111)) == sub_idx);

        case Slice_pattern::SIXTEENS:
            return ((tick & static_cast<uint8_t>(0b0000'1111)) == sub_idx);

        case Slice_pattern::THIRTYTWOS:
            return ((tick & static_cast<uint8_t>(0b0001'1111)) == sub_idx);

        case Slice_pattern::SIXTYFOURS:
            return ((tick & static_cast<uint8_t>(0b0011'1111)) == sub_idx);

        default:
            throw std::runtime_error("Unknown slice pattern.");
            return false;
    }
}

} // namespace THEA
