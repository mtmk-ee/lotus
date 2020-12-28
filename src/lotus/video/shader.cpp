
#include "lotus/video/shader.h"
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glcorearb.h>


using namespace lotus;


ShaderProgram::ShaderProgram(ShaderType type_) {
	
	switch ( type_ ) {
		case ShaderType::Vertex:
			type = GL_VERTEX_SHADER;
		case ShaderType::Fragment:
			type = GL_FRAGMENT_SHADER;
		default:
			throw std::runtime_error("[Shader] Invalid shader type: " + std::to_string((int)type_));
	}
	
	program = glCreateProgram();
}
ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program);
}

bool ShaderProgram::AddSource(const std::initializer_list<std::string> &files) {
	
	for (const std::string &file : files) {
		std::ifstream f(file);
		if ( !f.good() )
			throw std::runtime_error("[Shader] Cannot open source file: " + file);
		
		std::string source((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		f.close();
		
		unsigned shader = glCreateShader(type);
		shaders.push_back(shader);
		
		glShaderSource(shader, 1, &source.c_str(), NULL);
		glCompileShader(shader);
		
		// Check if the compilation was successful
		GLint success;
		GLchar info_log[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if ( !success ) {
			glGetShaderInfoLog(shader, 512, NULL, info_log);
			printf("[Shader] Compilation error: %s\n", info_log);
			throw std::runtime_error("[Shader] Compilation error: " + std::string((char*)info_log))
		}
		
		glAttachShader(program, shader);
	}
}
bool Link() {
	if ( linked )
		return true;
	
	glLinkProgram(program);
	
	// Check if the link was successful
	GLint success;
	GLchar info_log[512];
	glGetProgramiv(program_id, GL_LINK_STATUS, &success);
	if ( !success ) {
		glGetProgramInfoLog(program_id, 512, NULL, info_log);
		throw std::runtime_exception("[Shader] Program linker error: " + std::string((char*)info_log));
		return false;
	}
	else {
		return (linked = true);
	}
}
void Bind() {
	glUseProgram(program)
}
void Unbind() {
	glUseProgram(0);
}
