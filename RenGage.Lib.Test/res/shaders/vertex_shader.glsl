#version 460

//Note: Compiler will optimize away(discard) any unused attribute.
layout (location=0) in vec3 position;	//The vertex in the local coordinate coordinate system
layout (location=1) in vec3 normal;
layout (location=2) in vec2 tex_coord;

uniform mat4 mv_matrix;//Model-View matrix uniform
uniform mat4 proj_matrix;//Projection matrix uniform

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
}