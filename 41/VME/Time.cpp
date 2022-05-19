#include "Time.h"

Time::Time() {}

Time::~Time() {}

void Time::Start()
{
    frame_current = frame_current + 1;
    frame_total = frame_total + 1;
    elapsed = (Time::Get() - start_time);

    if (elapsed > 1.000)
    {
        start_time = Time::Get();

        frame_count = frame_current;
        frame_current = 0;
    }

    if (frame_total > (32767 - 8))
    {
        frame_total = 0;
    }
}

double Time::Get()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - p_start).count();
}

void Time::End()
{
    fixedTime = 1.0 / 144;
    deltaTime = Time::Get() - frame_start;
    totalTime = 1000.0 * (double(fixedTime) - double(deltaTime)) + 0.5;
    durationTime = (int)totalTime;

    frame_end = Time::Get();
    frame_start = frame_end;
}