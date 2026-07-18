#pragma once

#include <cstdint>


namespace THEA
{
namespace timeslicer
{

void init();
void tick();

enum class Slice_pattern
{
    ONES = 0,
    TWOS,
    FOURS,
    EIGHTS,
    SIXTEENS,
    THIRTYTWOS,
    SIXTYFOURS,
};

bool eval_tick_valid_timeslice(Slice_pattern slice_pattern, uint8_t sub_idx);

} // namespace timeslicer
} // namespace THEA
