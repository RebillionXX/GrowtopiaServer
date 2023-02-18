#include <Utils/TimingClock.hpp>

RebillionClockXD::RebillionClockXD() : m_time{ system_clock::now() } {}
RebillionClockXD::RebillionClockXD(const time_point& tp) : m_time{ tp } {}

time_point& RebillionClockXD::GetTimepoint() { 
    return this->m_time; 
}
long RebillionClockXD::GetDaysPassed() noexcept {
    return std::chrono::duration_cast<std::chrono::hours>(system_clock::now() - m_time).count() / 24;
}
int RebillionClockXD::GetHoursPassed() noexcept {
    return std::chrono::duration_cast<std::chrono::hours>(system_clock::now() - m_time).count();
}

std::string RebillionClockXD::GetString(const std::chrono::seconds& time) noexcept {
    static int day_count = 24 * 3600;
    static int hour_count = 3600;
    static int min_count = 60;

    int n = time.count();
    int days = n / day_count;
    n %= day_count;
    int hours = n / hour_count;
    n %= hour_count;
    int minutes = n / min_count;
    n %= min_count;
    int seconds = n;

    std::string result{};
    if (days > 0)
        return fmt::format("{} days, {} hours, {} mins, {} secs", days, hours, minutes, seconds);
    else if (hours > 0)
        return fmt::format("{} hours, {} mins, {} secs", hours, minutes, seconds);
    else if (minutes > 0)
        return fmt::format("{} mins, {} secs", minutes, seconds);
    else
        return fmt::format("{} secs", seconds);
    return result;
}

TimingClock::TimingClock() : m_time{ steady_clock::now() }, m_timeout{ std::chrono::seconds(0) } {}
TimingClock::TimingClock(const int32_t& timeOut) : m_time{ steady_clock::now() }, m_timeout{ std::chrono::seconds(timeOut) } {}
TimingClock::TimingClock(const std::chrono::seconds& timeOut) : m_time{ steady_clock::now() }, m_timeout{ timeOut } {}
TimingClock::TimingClock(const steady_clock::time_point& time, const std::chrono::seconds& timeOut) : m_time{ time }, m_timeout{ timeOut } {}

void TimingClock::UpdateTime() { 
    this->m_time = steady_clock::now(); 
}
void TimingClock::UpdateTime(const steady_clock::time_point& time) { 
    this->m_time = time; 
}
void TimingClock::UpdateTimeout(const int32_t& timeOut) { 
    this->m_timeout = std::chrono::seconds{ timeOut }; 
}
void TimingClock::UpdateTimeout(const std::chrono::seconds& timeOut) { 
    this->m_timeout = timeOut; 
}

steady_clock::time_point TimingClock::GetTime() const { 
    return this->m_time; 
}
std::chrono::seconds TimingClock::GetTimeout() const { 
    return this->m_timeout; 
}
std::chrono::seconds TimingClock::GetPassedTime() const { 
    return std::chrono::duration_cast<std::chrono::seconds>(steady_clock::now() - m_time); 
}