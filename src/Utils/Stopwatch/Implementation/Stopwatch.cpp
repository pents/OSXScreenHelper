//
// Created by Dmitry on 21.03.2023.
//

#include "Stopwatch.h"

stopwatch::Stopwatch::Stopwatch() : start_time(), laps({}) {
    start();
}

void stopwatch::Stopwatch::start() {
    start_time = std::chrono::high_resolution_clock::now();
    laps = {start_time};
}

template<stopwatch::TimeFormat fmt>
std::uint64_t stopwatch::Stopwatch::ticks(const stopwatch::Stopwatch::time_pt &start_time,
                                          const stopwatch::Stopwatch::time_pt &end_time) {
    const auto duration = end_time - start_time;
    const std::uint64_t ns_count = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

    switch(fmt){
        case TimeFormat::NANOSECONDS:
        {
            return ns_count;
        }
        case TimeFormat::MICROSECONDS:
        {
            std::uint64_t up = ((ns_count/100)%10 >= 5) ? 1 : 0;
            const auto mus_count = (ns_count /1000) + up;
            return mus_count;
        }
        case TimeFormat::MILLISECONDS:
        {
            std::uint64_t up = ((ns_count/100000)%10 >= 5) ? 1 : 0;
            const auto ms_count = (ns_count /1000000) + up;
            return ms_count;
        }
        case TimeFormat::SECONDS:
        {
            std::uint64_t up = ((ns_count/100000000)%10 >= 5) ? 1 : 0;
            const auto s_count = (ns_count /1000000000) + up;
            return s_count;
        }
    }
}

template<stopwatch::TimeFormat fmt_total, stopwatch::TimeFormat fmt_lap>
std::pair<std::uint64_t, std::vector<std::uint64_t>> stopwatch::Stopwatch::elapsed_laps() {
    std::vector<std::uint64_t> lap_times;
    lap_times.reserve(laps.size()-1);

    for( std::size_t idx = 0; idx <= laps.size()-2; idx++){
        const auto lap_end = laps[idx+1];
        const auto lap_start = laps[idx];
        lap_times.push_back( ticks<fmt_lap>(lap_start, lap_end) );
    }

    return { ticks<fmt_total>(start_time, laps.back()), lap_times };
}

template<stopwatch::TimeFormat fmt>
std::uint64_t stopwatch::Stopwatch::elapsed() {
    const auto end_time = std::chrono::high_resolution_clock::now();
    return ticks<fmt>(start_time, end_time);
}

template<stopwatch::TimeFormat fmt>
std::uint64_t stopwatch::Stopwatch::lap() {
    const auto t = std::chrono::high_resolution_clock::now();
    const auto last_r = laps.back();
    laps.push_back( t );
    return ticks<fmt>(last_r, t);
}

std::string stopwatch::show_times(const std::vector<std::uint64_t> &times) {
    std::string result("{");
    for( const auto& t : times ){
        result += std::to_string(t) + ",";
    }
    result.back() = static_cast<char>('}');
    return result;
}
