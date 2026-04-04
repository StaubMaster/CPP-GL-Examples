#version 330



struct Trans2D
{
	vec2 Pos;
	mat2 Rot;
};

struct PixelSize
{
	vec2 Full;
	vec2 Half;
};
struct sDisplaySize
{
	vec2 Ratio;
	PixelSize Window;
	PixelSize Buffer;
};



uniform sDisplaySize DisplaySize;
uniform mat3 View;
uniform float Scale;



layout(location = 0) in vec2 VPos;
layout(location = 1) in vec4 VCol;

layout(location = 2) in mat3 ITrans;



out Vert {
	vec4 Col;
} vs_out;



void main()
{
	vec2 pos = VPos;
	pos = (vec3(pos, 1) * ITrans).xy;
	pos = (vec3(pos, 1) * View).xy;
	pos = pos / Scale;

//	{
//		mat3x3 view_mat_pos = mat3x3(
//			1.0, 0.0, -View.Pos[0],
//			0.0, 1.0, -View.Pos[1],
//			0.0, 0.0, 1.0
//		);
//		mat3x3 view_mat_rot = mat3x3(
//			View.Rot[0][0], View.Rot[1][0], 0.0,
//			View.Rot[0][1], View.Rot[1][1], 0.0,
//			0.0           , 0.0           , 1.0
//		);
//		mat3x3 view_mat_scl = mat3x3(
//			1.0 / Scale, 0.0, 0.0,
//			0.0, 1.0 / Scale, 0.0,
//			0.0, 0.0, 1.0
//		);
//		mat3x3 view_mat = (view_mat_pos * view_mat_rot) * view_mat_scl;
//		vec3 pos3 = vec3(pos, 1);
//		pos3 = pos3 * view_mat;
//		pos = vec2(pos3.x, pos3.y);
//	}

	pos = pos * DisplaySize.Ratio;

	gl_Position = vec4(pos, 0, 1);

	vs_out.Col = VCol;
}
