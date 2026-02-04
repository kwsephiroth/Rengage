#version 460

// Inputs - Vertex Attributes
//Note: Compiler will optimize away(discard) any unused attribute.
layout (location=0) in vec3 position;	// The vertex in the local coordinate coordinate system
layout (location=1) in vec3 normal;
layout (location=2) in vec2 tex_coord;

// Uniforms
uniform mat4 mv_matrix; // Model-View matrix uniform
uniform mat4 proj_matrix; // Projection matrix uniform

// Texture sampler uniform. 
layout (binding=0) uniform sampler2D tex_sampler; // Binding 0 here indicates this sampler is to be associated with texture unit 0 (GL_TEXTURE0)

// Outputs
out vec2 forwarded_tex_coord;

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0f);
	forwarded_tex_coord = tex_coord;
}