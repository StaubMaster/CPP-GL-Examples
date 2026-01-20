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
	vec4		Color;
};



struct LightBase
{
	float	Intensity;
	vec4	Color;
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
uniform LightSolar Solar;
uniform LightSpot Spot;

const uint SpotLimit = uint(4);
uniform LightSpot[SpotLimit] SpotArr;
uniform uint SpotCount;



in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
} fs_inn;



out vec4 Color;



vec4 CalcLightFactor()
{
	vec4 ambient_factor = Ambient.Intensity * Ambient.Color;
	vec4 solar_factor = Solar.Base.Intensity * Solar.Base.Color * dot(Solar.Direction, normalize(fs_inn.Normal));

	vec4 spot_factor[SpotLimit];
	for (uint i = uint(0); i < SpotCount; i++)
	{
		vec3 spot_rel = normalize(fs_inn.Absolute - SpotArr[i].Position);
		float spot_dot;
		spot_dot = dot(spot_rel, SpotArr[i].Direction);
		spot_dot = (spot_dot - SpotArr[i].Range.Min) / SpotArr[i].Range.Len;
		spot_dot = min(1.0, max(0.0, spot_dot));
		spot_dot = spot_dot * dot(spot_rel, normalize(fs_inn.Normal));
		spot_dot = min(1.0, max(0.0, spot_dot));
		spot_factor[i] = SpotArr[i].Base.Intensity * SpotArr[i].Base.Color * spot_dot;
	}

	vec4 light_factor = vec4(0.0, 0.0, 0.0, 0.0);
	light_factor = max(light_factor, ambient_factor);
	light_factor = max(light_factor, solar_factor);
	for (uint i = uint(0); i < SpotCount; i++)
	{
		light_factor = max(light_factor, spot_factor[i]);
	}
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
	vec4	light_factor = CalcLightFactor();

	vec4 col = texture(texture0, fs_inn.Tex);

	col = col * light_factor;
	col = (col * (1.0 - depth_factor)) + (depth_factor * Depth.Color);

	//col = vec3(1.0 - depth_factor);		//	Depth
	//col = abs(normalize(fs_inn.Normal));	//	Normals
	Color = vec4(col.rgb, 1.0);
}
