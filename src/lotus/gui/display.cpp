
#include "lotus/gui/display.h"
#include "lotus/engine/engine.h"

#include "lotus/gui/glfw.h"
#include <GL/gl.h>


using namespace lotus;



std::unordered_map<WindowHandle, Display*> Display::display_map = std::unordered_map<WindowHandle, Display*>();



Display::Display() : handle(nullptr) {
	config = DisplayConfiguration();
}
Display::Display(const std::string &title) : handle(nullptr) {
	config = DisplayConfiguration();
	config.title = title;
}
Display::Display(const std::string &title, unsigned width, unsigned height) : handle(nullptr) {
	config = DisplayConfiguration();
	config.title = title;
	config.width = width;
	config.height = height;
}
Display::Display(const std::string &title, unsigned x, unsigned y, unsigned width, unsigned height) : handle(nullptr) {
	config = DisplayConfiguration();
	config.title = title;
	config.x = x;
	config.y = y;
	config.width = width;
	config.height = height;
}
Display::Display(const DisplayConfiguration &config) : config(config), handle(nullptr) {
	
}
Display::~Display() {
	if ( handle != nullptr )
		glfwDestroyWindow(handle);
}

void Display::Initialize() {
	if ( handle != nullptr )
		throw std::runtime_error("[Display] Display already initialized");
	
	glfwWindowHint(GLFW_RESIZABLE, config.resizable);
	glfwWindowHint(GLFW_DECORATED, config.decorated);
	glfwWindowHint(GLFW_FOCUSED, config.focused);
	glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
	glfwWindowHint(GLFW_DEPTH_BITS, config.depth_bits);
	glfwWindowHint(GLFW_ALPHA_BITS, config.alpha_bits);
	glfwWindowHint(GLFW_SAMPLES, config.samples);
	glfwWindowHint(GLFW_REFRESH_RATE, config.refresh_rate);
	glfwWindowHint(GLFW_DOUBLEBUFFER, config.double_buffer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config.opengl_version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config.opengl_version_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, config.opengl_forward_compatible);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	
	handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), NULL, NULL);
	if ( !handle )
		throw std::runtime_error("[Display] Failed to create window\n");
	display_map[handle] = this;
	
	if ( !config.maximized )
		glfwSetWindowPos(handle, config.x, config.y);
	
	glfwSetWindowPosCallback(handle, MoveCallback);
	glfwSetWindowSizeCallback(handle, ResizeCallback);
	glfwSetWindowCloseCallback(handle, CloseCallback);
	
}

void Display::Maximize() {
	glfwMaximizeWindow(handle);
}
void Display::Minimize() {
	glfwIconifyWindow(handle);
}
void Display::Restore() {
	glfwRestoreWindow(handle);
}

void Display::SetVisible(bool visible) {
	if ( visible )
		glfwShowWindow(handle);
	else
		glfwHideWindow(handle);
}
void Display::Close() {
	glfwSetWindowShouldClose(handle, GLFW_TRUE);
}
void Display::CancelClose() {
	glfwSetWindowShouldClose(handle, GLFW_FALSE);
}




void Display::MakeContextCurrent() {
	glfwMakeContextCurrent(handle);
}
void Display::Invalidate() {
	MakeContextCurrent();
	int width, height;
	glfwGetFramebufferSize(handle, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(135, 206, 235, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Display::Finalize() {
	MakeContextCurrent();
	glfwSwapBuffers(handle);
	glfwPollEvents();
}

void Display::ResizeCallback(WindowHandle handle, int width, int height) {
	Display *display = display_map[handle];
	for (auto listener : display->resize_listeners)
		listener->OnDisplayResize(width, height);
}
void Display::MoveCallback(WindowHandle handle, int x, int y) {
	Display *display = display_map[handle];
	for (auto listener : display->move_listeners)
		listener->OnDisplayMove(x, y);
}
void Display::CloseCallback(WindowHandle handle) {
	Display *display = display_map[handle];
	
	if ( display->close_listeners.size() == 0 ) {
		Engine::Instance()->Stop();
	}
	else {
		for (auto listener : display->close_listeners)
			listener->OnDisplayClose();
	}
}