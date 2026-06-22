#version 330



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

uniform mat4 View;

uniform DepthData Depth;

uniform float FOV;



layout(location = 0) in vec3 MainPos;
layout(location = 1) in vec3 MainNormal;
layout(location = 2) in vec3 MainTex;

//layout(location = 3) in vec3 InstPos; // 3
//layout(location = 4) in mat3 InstRot; // 4 5 6
layout(location = 3) in mat4 InstTrans; // 3 4 5 6

layout(location = 7) in mat4 InstNormal; // 7 8 9 10
layout(location = 11) in float InstScale;
layout(location = 12) in vec4 InstColor;



out Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
	vec4 Color;
} vs_out;



vec4 proj(in vec3 p_inn)
{
	vec4 p_out;

	float s = 1.0 / tan(FOV / 2.0);

	p_out.x = p_inn.x * s;
	p_out.y = p_inn.y * s;
	p_out.z = p_inn.z * Depth.Factors[5] - Depth.Factors[6];
	p_out.w = p_inn.z;

	p_out.x = p_out.x * DisplaySize.Ratio.x;
	p_out.y = p_out.y * DisplaySize.Ratio.y;

	return p_out;
}

void main()
{
	vec3 size = vec3(DisplaySize.Buffer.Half / InstScale, 1.0);

// this would calculate the Screen pos per Vertex
// outside it is done once per Isntance, so its more efficient

//	vec3 pos = MainPos; // this needs to use Instance Pos
//	pos = (vec4(pos, 1.0) * InstTrans).xyz;
//	pos = (vec4(pos, 1.0) * View).xyz;
//
//	vec4 pos4 = proj(pos);
//	pos = pos4.xyz / pos4.w;
//
//	pos = pos * size;

	//vs_out.Original = MainPos;
	//vs_out.Absolute = (vec4(vs_out.Original, 1.0) * InstTrans).xyz;
	//vs_out.Relative = vs_out.Absolute / size;
	//gl_Position = vec4(vs_out.Relative, 1.0);

	vs_out.Original = MainPos * InstScale;
	vs_out.Absolute = (vec4(vs_out.Original, 1.0) * InstTrans).xyz;
	vs_out.Relative = (vec4(vs_out.Absolute, 1.0) * View).xyz;
	gl_Position = proj(vs_out.Relative);

	vs_out.Normal = (vec4(MainNormal, 1.0) * InstNormal).xyz;
	vs_out.Tex = MainTex;
	vs_out.Color = InstColor;
}
