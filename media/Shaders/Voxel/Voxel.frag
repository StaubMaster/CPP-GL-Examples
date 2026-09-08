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



uniform sampler2DArray TextureImage;



uniform LightBase Light_Ambient;
uniform LightDirection Light_Solar;

//const uint Light_Spot_Limit = 4u;
//uniform uint Light_Spot_Count = 0u;
//uniform LightSpot[Light_Spot_Limit] Light_Spot;



in Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;
} fs_inn;



out vec4 Color;



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
	light_factor += CalcLightFactor(Light_Ambient);
	light_factor += CalcLightFactor(Light_Solar);
	/*for (uint i = 0u; i < min(PointLimit, Lights.PointCount); i++)
	{
		light_factor += CalcLightFactor(Lights.Point[i]);
	}*/
	/*for (uint i = 0u; i < min(Light_Spot_Limit, Light_Spot_Count); i++)
	{
		light_factor += CalcLightFactor(Light_Spot[i]);
	}*/
	//light_factor = vec4(1.0);
	return light_factor;
}

/*vec4 CalcLightFactor()
{
	vec4 ambient_factor = Ambient.Intensity * Ambient.Color;
	vec4 solar_factor = Solar.Base.Intensity * Solar.Base.Color * dot(Solar.Direction, normalize(-fs_inn.Normal));

	vec4 spot_factor[SpotLimit];
	for (uint i = 0u; i < SpotCount; i++)
	{
		vec3 spot_rel = normalize(fs_inn.Absolute - SpotArr[i].Position);
		float spot_dot;
		spot_dot = dot(spot_rel, SpotArr[i].Direction);
		spot_dot = (spot_dot - SpotArr[i].Range.Min) / SpotArr[i].Range.Len;
		spot_dot = min(1.0, max(0.0, spot_dot));
		spot_dot = spot_dot * dot(spot_rel, normalize(-fs_inn.Normal));
		spot_dot = min(1.0, max(0.0, spot_dot));
		spot_factor[i] = SpotArr[i].Base.Intensity * SpotArr[i].Base.Color * spot_dot;
	}

	vec4 light_factor = vec4(0.0, 0.0, 0.0, 0.0);
	light_factor = max(light_factor, ambient_factor);
	light_factor = max(light_factor, solar_factor);
	for (uint i = 0u; i < SpotCount; i++)
	{
		light_factor = max(light_factor, spot_factor[i]);
	}
	return light_factor;
}*/



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
