
#ifndef LOTUS_VIDEO_VERTEX_H
#define LOTUS_VIDEO_VERTEX_H

#include "lotus/util/math/vector.h"

namespace lotus {
	
	
	struct Vertex {
		vec3 position;
		vec2 texture;
		vec3 normal;
		
		Vertex(const vec3 &position, const vec2 &texture, const vec3 &normal) : position(position), texture(texture), normal(normal) {}
	};
	
	
}

#endif