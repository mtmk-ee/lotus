
#ifndef LOTUS_GUI_DISPLAY_H
#define LOTUS_GUI_DISPLAY_H

#include <string>
#include <vector>
#include <unordered_map>

#include "lotus/util/math/vector.h"
#include "lotus/gui/display_listeners.h"


typedef struct GLFWwindow GLFWwindow;
using WindowHandle = GLFWwindow*;



namespace lotus {
	
	
	struct DisplayConfiguration {
		int x = 100, y = 100;
		unsigned width = 820, height = 600;
		std::string title = "Lotus Game Engine";
		
		bool resizable = true;
		bool decorated = true;
		bool focused = true;
		bool maximized = false;
		unsigned depth_bits = 24;
		unsigned alpha_bits = 8;
		unsigned samples = 2;
		unsigned refresh_rate = 60;
		bool double_buffer = true;
		unsigned opengl_version_major = 3;
		unsigned opengl_version_minor = 3;
		bool opengl_forward_compatible = false;
		
	};
	
	
	class Display {
	public:
		Display();
		Display(const std::string &title);
		Display(const std::string &title, unsigned width, unsigned height);
		Display(const std::string &title, unsigned x, unsigned y, unsigned width, unsigned height);
		Display(const DisplayConfiguration &config);
		~Display();
		
		void SetTitle(const std::string &title);
		const std::string &GetTitle() const;
		
		void SetWidth(unsigned width);
		void SetHeight(unsigned height);
		void SetX(unsigned x);
		void SetY(unsigned y);
		void SetSize(unsigned width, unsigned height);
		void SetPosition(unsigned x, unsigned y);
		void SetFrame(unsigned x, unsigned y, unsigned width, unsigned height);
		unsigned GetX() const;
		unsigned GetY() const;
		unsigned GetWidth() const;
		unsigned GetHeight() const;
		
		void Maximize();
		void Minimize();
		void Restore();
		
		
		void Initialize();
		void SetVisible(bool visible);
		void Close();
		void CancelClose();
		
		void MakeContextCurrent();
		void Invalidate();
		void Finalize();
		
		
		inline void SetConfiguration(const DisplayConfiguration &config) {
			this->config = config;
		}
		
	
	private:
		static std::unordered_map<WindowHandle, Display*> display_map;
		
		DisplayConfiguration config;
		std::vector<DisplayCloseListener*> close_listeners;
		std::vector<DisplayMoveListener*> move_listeners;
		std::vector<DisplayResizeListener*> resize_listeners;
	
		WindowHandle handle;
		
		
		
		static void ResizeCallback(WindowHandle handle, int width, int height);
		static void MoveCallback(WindowHandle handle, int x, int y);
		static void CloseCallback(WindowHandle handle);
		
	};
	
	
}





#endif