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

struct LightDirection
{
	LightBase	Base;
	vec3		Direction;
};

struct LightPoint
{
	LightBase	Base;
	vec3		Position;
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
//   Light
//     Diffuse
//     Specular
//   BumpMap
uniform sampler2DArray TextureImage;



const uint SpotLimit = 4u;
const uint PointLimit = 1u;

layout (std140) uniform ILights
{
	LightBase				Ambient;
	LightDirection			Solar;
	uint					PointCount;
	LightPoint[PointLimit]	Point;
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



// rotating View changes Specular
// I dont think it should do that
// fs_inn.Relative includes roation
// light.Position - fs_inn.Absolute is different
// so it changing with rotation might be correct ?



vec4 CalcLightFactor(LightBase light)
{
	return light.Intensity * light.Color;
}
vec4 CalcLightFactor(LightDirection light)
{
	vec3 N = +normalize(fs_inn.Normal);
	vec3 L = -normalize(light.Direction);
	vec3 V = -normalize(fs_inn.Relative);
	vec3 R = +normalize(reflect(light.Direction, N));

	float factor_diffuse;
	factor_diffuse = dot(L, N);
	factor_diffuse = clamp(factor_diffuse, 0.0, 1.0);

	float factor_specular;
	factor_specular = dot(R, V);
	factor_specular = clamp(factor_specular, 0.0, 1.0);
	factor_specular = pow(factor_specular, 8);

	float factor = (factor_diffuse + factor_specular);
	return light.Base.Intensity * light.Base.Color * factor;
}
vec4 CalcLightFactor(LightPoint light)
{
	float strength = 128.0f;
	vec3 rel = light.Position - fs_inn.Absolute;

	float dist = length(rel);
	float factor_dist = strength / (dist * dist); // just use length2 ?

	vec3 N = +normalize(fs_inn.Normal);
	vec3 L = +normalize(rel);
	vec3 V = -normalize(fs_inn.Relative);
	vec3 R = +normalize(reflect(rel, N));

	float factor_diffuse;
	factor_diffuse = dot(L, N);
	factor_diffuse = clamp(factor_diffuse, 0.0, 1.0);

	float factor_specular;
	factor_specular = dot(R, V);
	factor_specular = clamp(factor_specular, 0.0, 1.0);
	factor_specular = pow(factor_specular, 8);

	float factor = factor_dist * (factor_diffuse + factor_specular);
	return light.Base.Intensity * light.Base.Color * factor;
}
vec4 CalcLightFactor(LightSpot light)
{
	vec3 N = +normalize(fs_inn.Normal);
	vec3 L = +normalize(light.Position - fs_inn.Absolute);
	vec3 V = -normalize(fs_inn.Relative);
	vec3 R = +normalize(reflect(light.Direction, N));

	float factor_intensity;
	factor_intensity = dot(L, -normalize(light.Direction));
	factor_intensity = (factor_intensity - light.Range.Min) / light.Range.Len;
	factor_intensity = clamp(factor_intensity, 0.0, 1.0);

	float factor_diffuse;
	factor_diffuse = dot(L, N);
	factor_diffuse = clamp(factor_diffuse, 0.0, 1.0);

	float factor_specular;
	factor_specular = dot(R, V);
	factor_specular = clamp(factor_specular, 0.0, 1.0);
	factor_specular = pow(factor_specular, 8);

	float factor = factor_intensity * (factor_diffuse + factor_specular);
	return light.Base.Intensity * light.Base.Color * factor;
}
vec4 CalcLightFactor()
{
	vec4 light_factor = vec4(0.0, 0.0, 0.0, 0.0);
	light_factor += CalcLightFactor(Lights.Ambient);
	light_factor += CalcLightFactor(Lights.Solar);
	for (uint i = 0u; i < min(PointLimit, Lights.PointCount); i++)
	{
		light_factor += CalcLightFactor(Lights.Point[i]);
	}
	for (uint i = 0u; i < min(SpotLimit, Lights.SpotCount); i++)
	{
		light_factor += CalcLightFactor(Lights.Spot[i]);
	}
	//light_factor = vec4(1.0);
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
