#include "TimeCode.h"
#include <stdexcept>

using namespace std;


// Convert hour/minute/second components into one total-second value
// so TimeCode only needs to store one instance variable.
long long unsigned int TimeCode::ComponentsToSeconds(
    unsigned int hr,
    unsigned int min,
    unsigned long long int sec)
{
    return (long long unsigned int)hr * 3600
         + (long long unsigned int)min * 60
         + sec;
}


TimeCode::TimeCode(
    unsigned int hr,
    unsigned int min,
    long long unsigned int sec)
{
    t = ComponentsToSeconds(hr, min, sec);
}


TimeCode::TimeCode(const TimeCode& tc)
{
    t = tc.t;
}


void TimeCode::GetComponents(
    unsigned int& hr,
    unsigned int& min,
    unsigned int& sec) const
{
    hr = t / 3600;

    long long unsigned int remaining = t % 3600;

    min = remaining / 60;
    sec = remaining % 60;
}


unsigned int TimeCode::GetHours() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return hr;
}


unsigned int TimeCode::GetMinutes() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return min;
}


unsigned int TimeCode::GetSeconds() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return sec;
}


string TimeCode::ToString() const
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    return to_string(hr) + ":"
         + to_string(min) + ":"
         + to_string(sec);
}


void TimeCode::SetHours(unsigned int hours)
{
    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hours, min, sec);
}


void TimeCode::SetMinutes(unsigned int minutes)
{
    if (minutes >= 60)
    {
        throw invalid_argument("Minutes must be less than 60");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, minutes, sec);
}


void TimeCode::SetSeconds(unsigned int seconds)
{
    if (seconds >= 60)
    {
        throw invalid_argument("Seconds must be less than 60");
    }

    unsigned int hr;
    unsigned int min;
    unsigned int sec;

    GetComponents(hr, min, sec);

    t = ComponentsToSeconds(hr, min, seconds);
}


void TimeCode::reset()
{
    t = 0;
}


TimeCode TimeCode::operator+(const TimeCode& other) const
{
    TimeCode result;

    result.t = t + other.t;

    return result;
}


TimeCode TimeCode::operator-(const TimeCode& other) const
{
    if (other.t > t)
    {
        throw invalid_argument("TimeCode cannot be negative");
    }

    TimeCode result;

    result.t = t - other.t;

    return result;
}


TimeCode TimeCode::operator*(double a) const
{
    if (a < 0)
    {
        throw invalid_argument("Negative multiplier not allowed");
    }

    TimeCode result;

    result.t = (long long unsigned int)(t * a);

    return result;
}


TimeCode TimeCode::operator/(double a) const
{
    if (a <= 0)
    {
        throw invalid_argument("Division value must be positive");
    }

    TimeCode result;

    result.t = (long long unsigned int)(t / a);

    return result;
}


bool TimeCode::operator==(const TimeCode& other) const
{
    return t == other.t;
}


bool TimeCode::operator!=(const TimeCode& other) const
{
    return t != other.t;
}


bool TimeCode::operator<(const TimeCode& other) const
{
    return t < other.t;
}


bool TimeCode::operator<=(const TimeCode& other) const
{
    return t <= other.t;
}


bool TimeCode::operator>(const TimeCode& other) const
{
    return t > other.t;
}


bool TimeCode::operator>=(const TimeCode& other) const
{
    return t >= other.t;
}