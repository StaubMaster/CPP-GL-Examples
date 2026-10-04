#version 330



struct SRange
{
	float	Min;
	float	Len;
	float	Max;
};

struct SDepth
{
	float[7]	Factors;
	SRange		Range;
	vec4		Color;
};



struct SLightBase
{
	float	Intensity;
	vec4	Color;
};

struct SLightDirection
{
	SLightBase	Base;
	vec3		Direction;
};

struct SLightPoint
{
	SLightBase	Base;
	vec3		Position;
};

struct SLightSpot
{
	SLightBase	Base;
	vec3		Position;
	vec3		Direction;
	SRange		Range;
};



uniform SDepth Depth;



uniform sampler2DArray TextureImage;



const uint SpotLimit = 4u;
const uint PointLimit = 1u;

layout(std140) uniform ILights
{
	SLightBase					Ambient;
	SLightDirection				Solar;
	uint						PointCount;
	SLightPoint[PointLimit]		Point;
	uint						SpotCount;
	SLightSpot[SpotLimit]		Spot;
} Lights;



in Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;
} fs_inn;



out vec4 Color;



vec4 CalcLightFactor(SLightBase light)
{
	return light.Intensity * light.Color;
}
vec4 CalcLightFactor(SLightDirection light)
{
	vec3 N = +normalize(fs_inn.Normal);
	vec3 L = -normalize(light.Direction);
	vec3 V = -normalize(fs_inn.Relative);
	vec3 R = +normalize(reflect(light.Direction, N));
	if (dot(light.Direction, N) > 0.0)
	{
		R = vec3(0, 0, 0);
	}

	float factor_diffuse;
	factor_diffuse = dot(L, N);
	factor_diffuse = clamp(factor_diffuse, 0.0, 1.0);

	float factor_specular;
	factor_specular = dot(R, V);
	factor_specular = clamp(factor_specular, 0.0, 1.0);
	factor_specular = pow(factor_specular, 8);
	factor_specular = 0.0;

	float factor = (factor_diffuse + factor_specular);
	return light.Base.Intensity * light.Base.Color * factor;
}
vec4 CalcLightFactor(SLightPoint light)
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
vec4 CalcLightFactor(SLightSpot light)
{
	vec3 N = +normalize(fs_inn.Normal);
	vec3 L = +normalize(light.Position - fs_inn.Absolute);
	vec3 V = -normalize(fs_inn.Relative);
	vec3 R = +normalize(reflect(light.Direction, N));
	if (dot(light.Direction, N) > 0.0)
	{
		R = vec3(0, 0, 0);
	}

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

	vec4 col;
	col = texture(TextureImage, fs_inn.Tex);
//	col = vec4(1.0, 1.0, 1.0, 1.0);

	col = col * light_factor;
	col = (col * (1.0 - depth_factor)) + (depth_factor * Depth.Color);

//	col = vec4(abs(normalize(fs_inn.Normal)), 1);
	Color = col;
}
