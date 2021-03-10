#include "signal_time.h"

#include <chrono>

class ChronoTime
{
public:
    ChronoTime() :
        start_time(std::chrono::high_resolution_clock::now())
    {
        // Empty Constructor
    }

    efis_signals::timestamp_t get_millis() const
    {
        const auto period = std::chrono::high_resolution_clock::period();
        auto current_time = std::chrono::high_resolution_clock::now();

        double delta_ticks = static_cast<double>((current_time - start_time).count());

        return static_cast<efis_signals::timestamp_t>(delta_ticks * period.num * 1000.0 / period.den);
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

efis_signals::timestamp_t efis_signals::get_millis()
{
    static ChronoTime time;
    return time.get_millis();
}
