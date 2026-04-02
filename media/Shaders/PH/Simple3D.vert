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

uniform mat4 View;

uniform DepthData Depth;

uniform float FOV;



layout(location = 0) in vec3 VPos;
layout(location = 1) in vec3 VNorm;
layout(location = 2) in vec3 VTex;

//layout(location = 3) in vec3 IPos;
//layout(location = 4) in mat3 IRot;
layout(location = 3) in mat4 IMat;



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
	vs_out.Original = VPos;

	vs_out.Absolute = (vec4(vs_out.Original, 1) * IMat).xyz;
	vs_out.Relative = (vec4(vs_out.Absolute, 1) * View).xyz;
	gl_Position = proj(vs_out.Relative);

//	vs_out.Normal = -(VNorm * (IRot));
//	vs_out.Normal = -(VNorm * transpose(IRot));
	vs_out.Tex = VTex;
}
