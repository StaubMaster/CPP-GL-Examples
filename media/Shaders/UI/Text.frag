#version 330



struct BoxF2
{
	vec2	Min;
	vec2	Max;
};



uniform sampler2DArray texture0;



in UI_Text
{
	vec2	PalletPos; // Font Pos
	BoxF2	Bound;
	vec4	Color0;
	vec4	Color1;
} fs_inn;



out vec4 Color;



void main()
{
	if (gl_FragCoord.x < fs_inn.Bound.Min.x ||
		gl_FragCoord.x > fs_inn.Bound.Max.x ||
		gl_FragCoord.y < fs_inn.Bound.Min.y ||
		gl_FragCoord.y > fs_inn.Bound.Max.y)
	{ discard; }

	vec4 col = texture(texture0, vec3(fs_inn.PalletPos, 0));
	if (col.a == 0) { discard; }

	vec4 col0 = vec4(0 + col.r, 0 + col.g, 0 + col.b, col.a);
	vec4 col1 = vec4(1 - col.r, 1 - col.g, 1 - col.b, col.a);
	Color = (col0 * fs_inn.Color0) + (col1 * fs_inn.Color1);
}
