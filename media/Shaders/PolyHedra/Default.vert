#version 330



struct Trans3D
{
	vec3	Pos;
	mat3	Rot;
};

struct PixelSize
{
	vec2	Full;
	vec2	Half;
};
struct sDisplaySize
{
	vec2		Ratio;
	PixelSize	Window;
	PixelSize	Buffer;
};

struct RangeData
{
	float	Min;
	float	Len;
	float	Max;
};

struct DepthData
{
	float[7]	Factors;
	RangeData	Range;
	vec4		Color;
};



uniform sDisplaySize DisplaySize;

uniform mat4 View;

uniform DepthData Depth;

uniform float FOV;



layout(location =  0) in vec3 MainPos;
layout(location =  1) in vec3 MainNormal;
layout(location =  2) in vec3 MainTex;
layout(location =  3) in vec4 MainColor;

layout(location =  4) in mat4 InstTrans; // 4 5 6 7
layout(location =  8) in vec4 InstColor;



out Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;
	vec4	Color;
} vs_out;



vec4 proj(in vec3 p_inn)
{
	vec4 p_out;

	float s = 1.0 / tan(FOV / 2.0);

	p_out.x = p_inn.x * s* DisplaySize.Ratio.x;
	p_out.y = p_inn.y * s* DisplaySize.Ratio.y;
	p_out.z = p_inn.z * Depth.Factors[5] - Depth.Factors[6];
	p_out.w = p_inn.z;

	return p_out;
}

void main()
{
	vs_out.Original = MainPos;
	vs_out.Absolute = (vec4(vs_out.Original, 1) * InstTrans).xyz;
	vs_out.Relative = (vec4(vs_out.Absolute, 1) * View).xyz;
	gl_Position = proj(vs_out.Relative);

	vs_out.Normal = (vec4(MainPos + MainNormal, 1) * InstTrans).xyz - vs_out.Absolute;
	vs_out.Tex = MainTex;
	vs_out.Color = MainColor;
}
