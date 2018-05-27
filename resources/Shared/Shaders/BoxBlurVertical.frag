uniform sampler2D texture;
uniform float blur_radius;

void main()
{
	vec2 textureSize = vec2( 800, 600 );
	vec2 tc = gl_TexCoord[0].xy;
	vec4 sum = vec4( 0.0 );
	vec4 base = texture2D( texture, tc );
	
	float normalFactor = 1 / textureSize.y;
	float normalizedRadius = blur_radius * normalFactor;
	float stepAverage = 1 / ( blur_radius * 2 );
	
	for( float i = tc.y - normalizedRadius; i < tc.y + normalizedRadius; i+= normalFactor )
	{
		vec4 cdstcol = texture2D( texture, vec2( tc.x, i) );
		sum += cdstcol;
	}
	
	vec3 resColor = sum.xyz / sum.w;
	float resAlpha = sum.w / blur_radius * 2;
	
    gl_FragColor = vec4( resColor, resAlpha );
}

