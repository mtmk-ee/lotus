
#ifndef LOTUS_GUI_GLFW_H
#define LOTUS_GUI_GLFW_H

#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#include <iostream>

namespace lotus {
	
	class GLFW {
	public:
		
		inline static void Initialize() {
			static bool initialized = false;
			
			if ( !initialized ) {
				if ( glfwInit() )
					initialized = true;
				else
					throw std::runtime_error("[GLFW] Failed to initialize GLFW3");
			}
		}
		
		inline static void Terminate() {
			glfwTerminate();
		}
		
	private:
		GLFW() = delete;
	};
	
	
	
}

#endif