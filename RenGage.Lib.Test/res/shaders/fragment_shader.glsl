#version 460

layout (binding=0)  uniform sampler2D tex_sampler; // Texture sampler uniform
in vec2 forwarded_tex_coord;
out vec4 color;

void main(void)
{
	//color = vec4(0.0f, 1.0f, 0.0f, 1.0f);//(R, G, B, A)
	color = texture (tex_sampler, forwarded_tex_coord);
	//vec4 texel = texture (tex_sampler, forwarded_tex_coord);

	//test for alpha channel from texel
	//if (texel.w < 1) // has transparency
		//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//else
		//color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}