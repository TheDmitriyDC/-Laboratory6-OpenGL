#pragma once
#include <chrono>

class Time
{
public:
	Time();
	~Time();
public:
	/// <summary>
	/// Starts time measurement.
	/// </summary>
	void Start();
	/// <summary>
	/// Gets time from start.
	/// </summary>
	/// <returns> Time from application start. </returns>
	double Get();
	/// <summary>
	/// Finishes time measurement.
	/// </summary>
	void End();
public:
	// TIME
	unsigned int frame_count = 0;
	unsigned int frame_total = 0;
	unsigned int frame_current = 0;

	double start_time = 0.0;
	double elapsed = 0.0;
	double frame_start = 0.0;
	double frame_end = 0.0;
	// ----

	double initItme = 0.0;

	// VARIABLES
	double fixedTime = 0.0;
	double deltaTime = 0.0;
	double totalTime = 0.0;
	// ---------
	int durationTime = (int)totalTime;

	std::chrono::steady_clock::time_point p_start;
};