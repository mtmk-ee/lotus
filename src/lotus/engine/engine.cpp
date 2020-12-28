
#include "lotus/engine/engine.h"
#include "lotus/gui/glfw.h"


using namespace lotus;

Engine* Engine::instance = nullptr;


Engine::Engine() {
	if ( instance != nullptr )
		throw std::runtime_error("[Engine] Only a single instance of the engine may be running at a time");
	else
		instance = this;
	
	target_ups = 120;
	target_fps = 60;
	running = false;
	
	GLFW::Initialize();
}
Engine::~Engine() {
	GLFW::Terminate();
}



void Engine::Start() {
	if ( IsRunning() )
		return;
	
	running = true;
	
	display.Initialize();
	display.SetVisible(true);
	
	
	// Start the update thread
	update_thread = std::thread(Engine::UpdateLoop, this);
	
	
	
	
	Timer timer, print_timer;
	Duration delta;
	Duration target_delta;
	timer.Start();
	print_timer.Start();
	int frame_count = 0;
	
	while ( running ) {
		delta = timer.Duration();
		target_delta = 1.0 / target_fps;
		
		// Check if listeners should be updated
		if ( delta >= target_delta ) {
			timer.Start();
			display.Invalidate();
			
			// Invoke listeners
			for (RenderListener *listener : render_listeners) {
				listener->Render();
			}
			
			display.Finalize();
			
			++frame_count;
		}
		else {
			// Sleep until the target duration is reached
			(target_delta - delta).Sleep();
		}
		
		if ( print_timer.Duration() > 1 ) {
			printf("[Engine] FPS: %d\n", frame_count);
			print_timer.Start();
			measured_fps = frame_count;
			frame_count = 0;
		}
	}
	
	update_thread.join();
}

void Engine::Stop() {
	running = false;
}



void Engine::UpdateLoop(Engine *engine) {
	
	Timer timer, print_timer;
	Duration delta;
	Duration target_delta;
	timer.Start();
	print_timer.Start();
	int update_count = 0;
	
	while ( engine->running ) {
		delta = timer.Duration();
		target_delta = 1.0 / engine->target_ups;
		
		// Check if listeners should be updated
		if ( delta >= target_delta ) {
			
			timer.Start();
			
			// Invoke listeners
			for (UpdateListener *listener : engine->update_listeners) {
				listener->Update();
			}
			
			++update_count;
		}
		else {
			// Sleep until the target duration is reached
			(target_delta - delta).Sleep();
		}
		
		
		if ( print_timer.Duration() > 1 ) {
			printf("[Engine] UPS: %d\n", update_count);
			print_timer.Start();
			engine->measured_ups = update_count;
			update_count = 0;
		}
	}
}



