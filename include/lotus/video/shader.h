
#ifndef LOTUS_VIDEO_SHADER_H
#define LOTUS_VIDEO_SHADER_H

#include <string>
#include <vector>

namespace lotus {
	
	
	enum class ShaderType {
		Vertex,
		Fragment
	};
	
	class ShaderProgram {
	public:
		ShaderProgram(ShaderType type);
		~ShaderProgram();
		
		bool AddSources(const std::initializer_list<std::string> &files);
		bool Link();
		void Bind();
		void Unbind();
		
		
	private:
		unsigned type;
		unsigned program;
		bool linked = false;
		std::vector<unsigned> shaders;
		
	};
	
	
}

#endif
