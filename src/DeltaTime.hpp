#pragma once
#include <chrono>


//Dedicated class for handling loop timing.
class DeltaTime
{
    using clock = std::chrono::steady_clock;
private: //FPS related variables
    std::chrono::time_point<clock> start_time;
    long long target_nano = 0;
    std::chrono::time_point<clock> previous_time;
    float frame_dt = 0;
    float current_time = 0;
private: //stopwatch variables
    std::chrono::time_point<clock> stopwatch_timer;
public:
    DeltaTime();
    //Handles timing! Place this function inside loops.
    void handle_time();

    //Sets the target fps.
    void set_target_fps(unsigned int fps);

    //Returns the current time between frames in seconds.
    float frame_time() const;
    
    //Returns time passed in seconds.
    float get_time() const;

    //Returns current fps.
    float get_fps() const;

public: //stopwatch

    //Starts stopwatch. Use stopwatch_f to finish.
    void stopwatch_s();
    //Stops stopwatch and returns duration in ms.
    float stopwatch_f();

};
inline DeltaTime::DeltaTime() : previous_time(clock::now()), start_time(clock::now()), target_nano(0){}
inline float DeltaTime::frame_time() const{ return frame_dt; }
inline float DeltaTime::get_time() const {return std::chrono::duration<float, std::ratio<1,1>>(clock::now() - start_time).count();}
inline float DeltaTime::get_fps() const{ return 1.0f/frame_dt; }
inline void DeltaTime::set_target_fps(unsigned int fps){ target_nano = fps? 1000000000 / fps: 0; }
inline void DeltaTime::handle_time()
{
    while(target_nano > std::chrono::duration<long long, std::nano>(clock::now() - previous_time).count()){}
    frame_dt = std::chrono::duration<float, std::ratio<1,1>>(clock::now() - previous_time).count(); 
    previous_time = clock::now();
}


inline void DeltaTime::stopwatch_s(){ stopwatch_timer = clock::now();}
inline float DeltaTime::stopwatch_f() { return std::chrono::duration<float, std::milli>(clock::now() - stopwatch_timer).count();}

