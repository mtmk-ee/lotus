
#ifndef LOTUS_ENGINE_ENGINE_H
#define LOTUS_ENGINE_ENGINE_H

#include <vector>
#include <thread>

#include "lotus/util/time.h"
#include "lotus/engine/listeners.h"
#include "lotus/gui/display.h"

namespace lotus {
	
	
	
	class Engine {
	public:
		Engine();
		~Engine();
		
		inline Display& GetDisplay() {
			return display;
		}
		inline const Display& GetDisplay() const {
			return display;
		}
		
		inline static Engine* Instance() {
			return instance;
		}
		
		inline bool IsRunning() const {
			return running;
		}
		
		inline void SetTargetUpdateRate(unsigned updates_per_second) {
			target_ups = updates_per_second;
		}
		inline void SetTargetRenderRate(unsigned frames_per_second) {
			target_fps = frames_per_second;
		}
		inline unsigned GetTargetUpdateRate() const {
			return target_ups;
		}
		inline unsigned GetTargetRenderRate() const {
			return target_fps;
		}
		inline unsigned GetUpdateRate() const {
			return measured_ups;
		}
		inline unsigned GetRenderRate() const {
			return measured_fps;
		}
		
		void Start();
		void Stop();
		
		
	private:
		static Engine *instance;
		
		Display display;
	
		std::vector<UpdateListener*> update_listeners;
		std::vector<RenderListener*> render_listeners;
		unsigned target_ups, measured_ups;
		unsigned target_fps, measured_fps;
		
		std::thread update_thread;
		
		
		bool running = false;
		
		static void UpdateLoop(Engine *engine);
		static void RenderLoop(Engine *engine);
	};
	
	
	
}

#endif