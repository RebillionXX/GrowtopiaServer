#pragma once
#include <chrono>
#include <fmt/chrono.h>

using high_resolution_clock = std::chrono::high_resolution_clock;
using system_clock = std::chrono::system_clock;
using steady_clock = std::chrono::steady_clock;
using time_point =  system_clock::time_point;

class RebillionClockXD {
public:
    RebillionClockXD();
    RebillionClockXD(const time_point& tp);

    time_point& GetTimepoint();
    long GetDaysPassed() noexcept;
    int GetHoursPassed() noexcept;

public:
    static std::string GetString(const std::chrono::seconds& time) noexcept;

private:
    system_clock::time_point m_time;
};

class TimingClock {
public:
    TimingClock();
    TimingClock(const int32_t& timeOut);
    TimingClock(const std::chrono::seconds& timeOut);
    TimingClock(const steady_clock::time_point& timePoint, const std::chrono::seconds& timeOut);

    void UpdateTime();
    void UpdateTime(const steady_clock::time_point& timePoint);
    void UpdateTimeout(const int32_t& timeOut);
    void UpdateTimeout(const std::chrono::seconds& timeOut);

    steady_clock::time_point GetTime() const;
    std::chrono::seconds GetTimeout() const;
    std::chrono::seconds GetPassedTime() const;
    
private:
    steady_clock::time_point m_time{ steady_clock::now() };
    std::chrono::seconds m_timeout{};
};