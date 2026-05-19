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


//	None  = 0b000,
//	PrevX = 0b001,
//	PrevY = 0b010,
//	PrevZ = 0b100,
//	NextX = 0b110,
//	NextY = 0b101,
//	NextZ = 0b011,
//	Here  = 0b111,

const vec3 axis[8] = vec3[8](
	vec3( 0,  0,  0), // None  = 0b000
	vec3(-1,  0,  0), // PrevX = 0b001
	vec3( 0, -1,  0), // PrevY = 0b010
	vec3( 0,  0, +1), // NextZ = 0b011
	vec3( 0,  0, -1), // PrevZ = 0b100
	vec3( 0, +1,  0), // NextY = 0b101
	vec3(+1,  0,  0), // NextX = 0b110
	vec3( 0,  0,  0)  // Here  = 0b111
);



uniform sDisplaySize DisplaySize;

uniform mat4 View;

uniform DepthData Depth;

uniform float FOV;



layout(location = 0) in uint Main_Voxel;
layout(location = 1) in uint Main_Tex;
layout(location = 2) in ivec3 Main_Chunk;



out Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;
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
	vs_out.Original.x = ((Main_Voxel >>  0) & 0xFFu);
	vs_out.Original.y = ((Main_Voxel >>  8) & 0xFFu);
	vs_out.Original.z = ((Main_Voxel >> 16) & 0xFFu);

	vs_out.Original.x += ((Main_Voxel >> 29) & 0x1u);
	vs_out.Original.y += ((Main_Voxel >> 30) & 0x1u);
	vs_out.Original.z += ((Main_Voxel >> 31) & 0x1u);

	vs_out.Absolute = vs_out.Original + Main_Chunk * 32;
	vs_out.Relative = (vec4(vs_out.Absolute, 1) * View).xyz;
	gl_Position = proj(vs_out.Relative);

	vs_out.Tex.x = float((Main_Voxel >> 24) & 0x1u);
	vs_out.Tex.y = float((Main_Voxel >> 25) & 0x1u);
	vs_out.Tex.z = Main_Tex;

	vs_out.Normal = axis[(Main_Voxel >> 26) & 0x7u];
}
