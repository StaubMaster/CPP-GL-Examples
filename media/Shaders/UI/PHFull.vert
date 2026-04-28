#version 330



struct Trans3D
{
	vec3 Pos;
	mat3 Rot;
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

struct RangeData
{
	float Min;
	float Len;
	float Max;
};

struct DepthData
{
	float[7]	Factors;
	RangeData	Range;
	vec4		Color;
};



uniform sDisplaySize DisplaySize;

//uniform mat4 View;

//uniform DepthData Depth;

//uniform float FOV;



layout(location = 0) in vec3 VPos;
layout(location = 1) in vec3 VNormal;
layout(location = 2) in vec3 VTex;

layout(location = 3) in mat4 ITrans; // 3 4 5 6
layout(location = 7) in mat4 INormal; // 7 8 9 10



out Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
} vs_out;



vec4 proj(in vec3 p_inn)
{
	vec4 p_out;

	p_out.x = p_inn.x;
	p_out.y = p_inn.y;
	p_out.z = p_inn.z;
	p_out.w = 1;

//	p_out.x = p_out.x * DisplaySize.Ratio.x;
//	p_out.y = p_out.y * DisplaySize.Ratio.y;

	return p_out;
}

/*
	#-------|---|-------------------# 33 Pixels
			|---| 4 Pixels
			| 9 Pixels
				| 13 Pixels

	0-------|---|-------------------1
			| 9 / 33 = 0.2727
				| 13 / 33 = 0.3939
			|---| [0.2727;0.3939] = 0.1212

	4 / 33 = 0.1212
*/
void main()
{
	vec2 size = vec2(40, 40);
	size = size / DisplaySize.Buffer.Full;
	size = size * vec2(2, 2);

// problem ?
// need to scale before rotating
// else depth dosent get scaled properly
// but scaling needs to be done before moving ?
// since moving relys on things being normalized ?
// normalize the position outside ?

	vs_out.Original = VPos;
//	vs_out.Original = VPos * vec3(size, 1);

	vs_out.Absolute = (vec4(vs_out.Original, 1) * ITrans).xyz;

//	vs_out.Relative = (vec4(vs_out.Absolute, 1) * View).xyz;
	vs_out.Relative = vs_out.Absolute * vec3(size, 1);
//	vs_out.Relative = vs_out.Absolute;

	gl_Position = proj(vs_out.Relative);

	vs_out.Normal = (vec4(VNormal, 1) * INormal).xyz;
	vs_out.Tex = VTex;
}
