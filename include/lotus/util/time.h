

#ifndef LOTUS_UTIL_TIME_H
#define LOTUS_UTIL_TIME_H

#include <chrono>
#include <thread>
#include <stdlib.h>


namespace lotus {
	
	class Duration {
		using DurationType = std::chrono::duration<double>;
	public:
		Duration(double seconds = 0) : duration((double)seconds) {}
		Duration(DurationType duration) : duration(duration) {}
		
		inline void Sleep() const {
			std::this_thread::sleep_for(duration);
		}
		
		
		
		inline unsigned long long Nanoseconds() const {
			return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		}
		
		//! Converts this time to seconds
		inline double Seconds() const {
			return std::chrono::duration<double>(duration).count();
		}
		//! Converts this time to minutes
		inline double Minutes() const {
			return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::minutes>(duration)).count();
		}
		//! Converts this time to hours
		inline double Hours() const {
			return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::hours>(duration)).count();
		}
		//! Converts this time to days
		inline double Days() const {
			return Hours() / 24;
		}
		
		inline bool operator ==(const Duration &other) const {
			return duration == other.duration;
		}
		inline bool operator !=(const Duration &other) const {
			return duration != other.duration;
		}
		inline bool operator >(const Duration &other) const {
			return duration > other.duration;
		}
		inline bool operator >=(const Duration &other) const {
			return duration >= other.duration;
		}
		inline bool operator <(const Duration &other) const {
			return duration < other.duration;
		}
		inline bool operator <=(const Duration &other) const {
			return duration <= other.duration;
		}
		
		
		inline Duration operator +(const Duration &other) const {
			return duration + other.duration;
		}
		inline Duration& operator +=(const Duration &other) {
			duration += other.duration;
			return *this;
		}
		inline Duration operator -(const Duration &other) const {
			return duration - other.duration;
		}
		inline Duration& operator -=(const Duration &other) {
			duration -= other.duration;
			return *this;
		}
		
		inline Duration operator *(double scalar) const {
			return duration * scalar;
		}
		inline Duration& operator *=(double scalar) {
			duration *= scalar;
			return *this;
		}
		
		inline Duration operator /(double scalar) const {
			return duration / scalar;
		}
		inline Duration& operator /=(double scalar) {
			duration /= scalar;
			return *this;
		}
		
		
	private:
		DurationType duration;
	};
	
	
	class Time {
		using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	public:
		Time() : time(std::chrono::high_resolution_clock::now()) {
			
		}
		
		inline static Time Now() {
			return Time(std::chrono::high_resolution_clock::now());
		}
		
		
		
		inline bool operator ==(const Time &other) const {
			return time.time_since_epoch() == other.time.time_since_epoch();
		}
		
		inline bool operator >(const Time &other) const {
			return time.time_since_epoch() > other.time.time_since_epoch();
		}
		inline bool operator >=(const Time &other) const {
			return time.time_since_epoch() >= other.time.time_since_epoch();
		}
		
		inline bool operator <(const Time &other) const {
			return time.time_since_epoch() < other.time.time_since_epoch();
		}
		inline bool operator <=(const Time &other) const {
			return time.time_since_epoch() <= other.time.time_since_epoch();
		}
		
		
		inline Duration operator -(const Time &other) const {
			return Duration(time - other.time);
		}
		
	private:
		inline Time(const TimePoint &time) : time(time) {}
	
		TimePoint time;
		
		
	};
	
	
	
	
	
	class Timer {
	public:
		//! Starts the timer
		inline void Start() {
			start_time = Time::Now();
		}
		
		//! Returns the duration between when Timer::Start() was called,
		//! and when this function was called
		inline Duration Duration() const {
			return Time::Now() - start_time;
		}
		
	private:
		Time start_time;
	};
}


#endif