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

struct LInterData
{
	float T0;
	float T1;
};



uniform DepthData Depth;

uniform LInterData ColorToTex;
uniform LInterData ShowLightFactor;

uniform sampler2DArray texture0;



const vec3		LightSolar = normalize(vec3(-1, +3, -2));
const float		SpecularFactor = 0.5;



in Vert {
	vec3	Original;
	vec3	Absolute;
	vec3	Relative;

	vec3	Normal;
	vec3	Tex;

	vec4	Col;

	vec4	AmbientColor;
	vec4	DiffuseColor;
	float	SpecularPower;
	vec4	SpecularColor;
} fs_inn;



out vec4 Color;



vec4 CalcLightFactor()
{
	vec4 ambient_factor = fs_inn.AmbientColor;
	vec4 diffuse_factor = fs_inn.DiffuseColor * dot(normalize(fs_inn.Normal), LightSolar);

	vec3 solar_reflect = reflect(LightSolar, normalize(fs_inn.Normal));

	float reflect_dot;
	reflect_dot = dot(normalize(fs_inn.Relative), solar_reflect);
	reflect_dot = max(reflect_dot, 0.0);
	reflect_dot = pow(reflect_dot, fs_inn.SpecularPower);

	vec4 specular_factor = reflect_dot * SpecularFactor * fs_inn.SpecularColor;

	vec4 light_factor = vec4(0.0, 0.0, 0.0, 0.0);
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
	//float	depth_factor = CalcDepthFactor();
	vec4	light_factor = CalcLightFactor();

	light_factor = light_factor * ShowLightFactor.T0 + vec4(1, 1, 1, 1) * ShowLightFactor.T1;

	vec4 col;
	col = (fs_inn.Col * ColorToTex.T0) + (texture(texture0, fs_inn.Tex) * ColorToTex.T1);
	Color = col * light_factor;
}
