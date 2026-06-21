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

// more Textures
//  Light Scattering
//  BumpMap
uniform sampler2DArray TextureImage;



const uint SpotLimit = 4u;

layout (std140) uniform ILights
{
	LightBase				Ambient;
	LightSolar				Solar;
	uint					SpotCount;
	LightSpot[SpotLimit]	Spot;
} Lights;



in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec3 Tex;
} fs_inn;



out vec4 Color;



vec4 CalcLightFactor(LightBase light)
{
	return light.Intensity * light.Color;
}
vec4 CalcLightFactor(LightSolar light)
{
	float dot_factor = dot(light.Direction, normalize(-fs_inn.Normal));
	return light.Base.Intensity * light.Base.Color * dot_factor;
}
vec4 CalcLightFactor(LightSpot light)
{
	vec3 spot_rel = normalize(fs_inn.Absolute - light.Position);

	float spot_dot;
	spot_dot = dot(spot_rel, light.Direction);

	spot_dot = (spot_dot - light.Range.Min) / light.Range.Len;
	spot_dot = min(1.0, max(0.0, spot_dot));

	spot_dot = spot_dot * dot(spot_rel, normalize(-fs_inn.Normal));
	//spot_dot = min(1.0, max(0.0, spot_dot));

	return light.Base.Intensity * light.Base.Color * spot_dot;
}
void AccumulateLightFactor(inout vec4 factor, in vec4 new_factor)
{
	//factor = factor + new_factor;
	factor = max(factor, new_factor);
}
vec4 CalcLightFactor()
{
	vec4 light_factor = vec4(0.0, 0.0, 0.0, 0.0);
	AccumulateLightFactor(light_factor, CalcLightFactor(Lights.Ambient));
	AccumulateLightFactor(light_factor, CalcLightFactor(Lights.Solar));
	for (uint i = 0u; i < min(SpotLimit, Lights.SpotCount); i++)
	{
		AccumulateLightFactor(light_factor, CalcLightFactor(Lights.Spot[i]));
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

	vec4 col = texture(TextureImage, fs_inn.Tex);

	col = col * light_factor;
	col = (col * (1.0 - depth_factor)) + (depth_factor * Depth.Color);

	//Color = vec4(abs(normalize(fs_inn.Normal)), 1.0);
	Color = vec4(col.rgb, 1.0);
}
