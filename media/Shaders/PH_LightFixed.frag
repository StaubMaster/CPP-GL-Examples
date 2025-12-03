#version 330



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
	vec3		Color;
};



struct LightBase
{
	float	Intensity;
	vec3	Color;
};

struct LightSolar
{
	LightBase	Base;
	vec3		Direction;
};

struct LightSpot
{
	LightBase	Base;
	vec3		Position;
	vec3		Direction;
	RangeData	Range;
};



uniform DepthData Depth;

uniform sampler2DArray texture0;

uniform LightBase Ambient;
uniform LightSolar Solar = LightSolar(LightBase(1.0, vec3(1.0, 1.0, 1.0)), normalize(vec3(-1, -2, -3)));



in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec2 Tex;
} fs_inn;



out vec4 Color;



vec3 CalcLightFactor()
{
	vec3 ambient_factor = Ambient.Intensity * Ambient.Color;
	vec3 solar_factor = Solar.Base.Intensity * Solar.Base.Color * dot(Solar.Direction, normalize(fs_inn.Normal));

	vec3 light_factor = vec3(0.0, 0.0, 0.0);
	light_factor = max(light_factor, ambient_factor);
	light_factor = max(light_factor, solar_factor);
	return light_factor;
}

float CalcDepthFactor()
{
	float depth_factor;

	depth_factor = gl_FragCoord.z;
	depth_factor = Depth.Factors[4] / (Depth.Factors[3] - (depth_factor * Depth.Factors[2]));

	//depth_factor = length(fs_inn.Relative);

	depth_factor = (depth_factor - Depth.Factors[0]) / Depth.Factors[1];
	gl_FragDepth = depth_factor;

	depth_factor = (depth_factor - Depth.Range.Min) / Depth.Range.Len;
	depth_factor = min(max(depth_factor, 0), 1);

	return depth_factor;
}



void main()
{
	float	depth_factor = CalcDepthFactor();
	vec3	light_factor = CalcLightFactor();

	vec3 col = texture(texture0, vec3(fs_inn.Tex, 0)).rgb;
	//col = vec3(1.0, 1.0, 1.0);

	col = col * light_factor;
	col = (col * (1.0 - depth_factor)) + (depth_factor * Depth.Color);

	//col = vec3(1.0 - depth_factor);		//	Depth
	//col = abs(normalize(fs_inn.Normal));	//	Normals
	Color = vec4(col, 1);
}
