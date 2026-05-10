#version 330



layout(location = 0) in vec2 Main_Pos;
layout(location = 1) in vec2 Main_Tex;



out Vert {
	vec3	Tex;
} vs_out;


void main()
{
	gl_Position = vec4(Main_Pos, 0, 1);
	vs_out.Tex = vec3(Main_Tex, 0);
}
