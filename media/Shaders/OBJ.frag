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

struct LInterData
{
	float T0;
	float T1;
};



uniform DepthData Depth;

uniform LInterData ColorToTex;

uniform sampler2DArray texture0;



const vec3		LightSolar = normalize(vec3(-1, +3, -2));
const float		SpecularFactor = 0.5;



in Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;

	vec3	Col;

	vec3	AmbientColor;
	vec3	DiffuseColor;
	float	SpecularPower;
	vec3	SpecularColor;
} fs_inn;



out vec4 Color;



vec3 CalcLightFactor()
{
	vec3 ambient_factor = fs_inn.AmbientColor;
	vec3 diffuse_factor = fs_inn.DiffuseColor * dot(normalize(fs_inn.Normal), LightSolar);

	vec3 solar_reflect = reflect(LightSolar, normalize(fs_inn.Normal));

	float reflect_dot;
	reflect_dot = dot(normalize(fs_inn.Relative), solar_reflect);
	reflect_dot = max(reflect_dot, 0.0);
	reflect_dot = pow(reflect_dot, fs_inn.SpecularPower);

	vec3 specular_factor = reflect_dot * SpecularFactor * fs_inn.SpecularColor;

	vec3 light_factor = vec3(0.0, 0.0, 0.0);
	light_factor = light_factor + ambient_factor;
	light_factor = light_factor + diffuse_factor;
	light_factor = light_factor + specular_factor;
	return min(light_factor, 1.0);
}

float CalcDepthFactor()
{
	float depth_factor;

	depth_factor = gl_FragCoord.z;
	depth_factor = Depth.Factors[4] / (Depth.Factors[3] - (depth_factor * Depth.Factors[2]));

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

	vec3 col;
	col = (fs_inn.Col * ColorToTex.T0) + (texture(texture0, fs_inn.Tex).rgb * ColorToTex.T1);
	//col = vec3(1.0, 1.0, 1.0);
	//col = vec3(0.5, 0.5, 0.5);

	col = col * light_factor;
	//col = (col * (1.0 - depth_factor)) + (depth_factor * Depth.Color);

	//col = vec3(1.0 - depth_factor);	//	Depth
	//col = abs(normalize(fs_inn.Normal));	//	Normals
	//col = vec3(fs_inn.Tex.x, 0.0, fs_inn.Tex.y);	//	Texture

	//col = vec3(1,1,1);
	Color = vec4(col, 1);
}
