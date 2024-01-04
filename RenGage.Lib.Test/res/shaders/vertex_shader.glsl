#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 tex_coord;

//uniform mat4 mv_matrix;//Model-View Matrix uniform
//uniform mat4 proj_matrix;//Projection Matrix uniform

void main(void)
{
	//gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
	gl_Position = vec4(0.0f,0.0f,0.0f,1.0f);
}