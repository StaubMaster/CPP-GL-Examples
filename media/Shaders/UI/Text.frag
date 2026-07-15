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
	vec4	Color;
} fs_inn;



out vec4 Color;



void main()
{
	// if statement in Fragment Shader is bad ?
	// figure out a better way of doing this ?
	// maybe make it so outside values result in alpha <= 0

	if (gl_FragCoord.x < fs_inn.Bound.Min.x ||
		gl_FragCoord.x > fs_inn.Bound.Max.x ||
		gl_FragCoord.y < fs_inn.Bound.Min.y ||
		gl_FragCoord.y > fs_inn.Bound.Max.y)
	{ discard; }

	vec4 col = texture(texture0, vec3(fs_inn.PalletPos, 0));

	// when loading Font Texture
	// add Transparency to Pixels
	// so only alpha gets filtered here

	//if (col.a == 0) { discard; }
	//if (col.r >= 0.5) { discard; }
	//if (col.g >= 0.5) { discard; }
	//if (col.b >= 0.5) { discard; }

	Color = col;
}
