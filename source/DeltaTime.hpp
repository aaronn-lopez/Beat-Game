#pragma once
#include <chrono>
#include <thread>
#include <iostream>


class DeltaTime
{
	std::chrono::high_resolution_clock timer;
	using ms = std::chrono::duration<float, std::milli>;
public:
	DeltaTime() {};
	void handle_time();
	void show_fps();
	float frame_time() { return deltaTime; }
	float get_time();
	void set_target_fps(float FPS_TARGET);
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start = timer.now();
	int fps_counter = 0;
	float dt_target = 0;
	float deltaTime = 0;
	float FPS = 0;
	float AVG_FPS = 0;
};

inline float DeltaTime::get_time()
{
	auto static start_i = timer.now();
	auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - start_i);
	return duration_ms.count() / 1000.0f;
}
inline void DeltaTime::handle_time()
{
	//static auto start = timer.now();
	while (std::chrono::duration_cast<ms>(timer.now() - start).count() < dt_target) {}
	deltaTime = std::chrono::duration_cast<ms>(timer.now() - start).count() * 0.001;
	start = timer.now();
}
inline void DeltaTime::show_fps()
{
	fps_counter++;
	FPS += 1 / deltaTime;
	if (fps_counter >= 100)
	{
		//std::cout << FPS / float(100) << '\n';
		AVG_FPS = FPS / float(100);
		FPS = 0;
		fps_counter = 0;
	}
	std::cout << AVG_FPS << '\n';
}
inline void DeltaTime::set_target_fps(float FPS_TARGET)
{
	if (FPS_TARGET == 0)
	{
		dt_target = 0;
		return;
	}
	dt_target = 1000 / FPS_TARGET;
}