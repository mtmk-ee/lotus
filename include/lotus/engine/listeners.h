

#ifndef LOTUS_ENGINE_LISTENERS_H
#define LOTUS_ENGINE_LISTENERS_H

#include "lotus/util/time.h"

namespace lotus {
	
	
	class UpdateListener {
	public:
		UpdateListener() {}
		virtual ~UpdateListener() {}
		
		virtual void Update() {
			last_tick_time = tick_time;
			tick_time = Time::Now();
		};
		
	protected:
		Time tick_time;
		Time last_tick_time;
		
		inline Duration GetDeltaTime() const {
			return last_tick_time == tick_time ? 0.008333 : tick_time - last_tick_time;
		}
	};
	
	class RenderListener {
	public:
		RenderListener() {}
		virtual ~RenderListener() {}
		
		virtual void Render() {
			last_tick_time = tick_time;
			tick_time = Time::Now();
		};
		
	protected:
		Time tick_time;
		Time last_tick_time;
		
		inline Duration GetDeltaTime() const {
			return last_tick_time == tick_time ? 0.016667 : tick_time - last_tick_time;
		}
	};
	
}



#endif