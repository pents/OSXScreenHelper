//
// Created by Dmitry on 21.03.2023.
//

#ifndef SCREENHELPER_STOPWATCH_H
#define SCREENHELPER_STOPWATCH_H

#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace stopwatch{

    enum TimeFormat{ NANOSECONDS, MICROSECONDS, MILLISECONDS, SECONDS };

    class Stopwatch{
    public:
        Stopwatch();

        void start();

        template<TimeFormat fmt = TimeFormat::MILLISECONDS>
        std::uint64_t lap();

        template<TimeFormat fmt = TimeFormat::MILLISECONDS>
        std::uint64_t elapsed();

        template<TimeFormat fmt_total = TimeFormat::MILLISECONDS, TimeFormat fmt_lap = fmt_total>
        std::pair<std::uint64_t, std::vector<std::uint64_t>> elapsed_laps();


    private:
        typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_pt;
        time_pt start_time;
        std::vector<time_pt> laps;

        template<TimeFormat fmt = TimeFormat::MILLISECONDS>
        static std::uint64_t ticks( const time_pt& start_time, const time_pt& end_time);
    };


constexpr TimeFormat ns =  TimeFormat::NANOSECONDS;
constexpr TimeFormat mus = TimeFormat::MICROSECONDS;
constexpr TimeFormat ms =  TimeFormat::MILLISECONDS;
constexpr TimeFormat s =   TimeFormat::SECONDS;

constexpr TimeFormat nanoseconds =  TimeFormat::NANOSECONDS;
constexpr TimeFormat microseconds = TimeFormat::MICROSECONDS;
constexpr TimeFormat milliseconds = TimeFormat::MILLISECONDS;
constexpr TimeFormat seconds =      TimeFormat::SECONDS;


std::string show_times( const std::vector<std::uint64_t>& times );

}

#endif //SCREENHELPER_STOPWATCH_H
