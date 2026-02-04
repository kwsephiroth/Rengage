#version 460

layout (binding=0)  uniform sampler2D tex_sampler; // Texture sampler uniform
in vec2 forwarded_tex_coord;
out vec4 color;

void main(void)
{
	//color = vec4(0.0f, 1.0f, 0.0f, 1.0f);//(R, G, B, A)
	color = texture (tex_sampler, forwarded_tex_coord);
}