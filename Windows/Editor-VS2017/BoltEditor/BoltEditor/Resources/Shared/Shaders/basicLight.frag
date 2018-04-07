// Version du GLSL
#version 330 compatibility

// IN
in vec3 vColor;

// Fonction main
void main()
{
	gl_FragColor = vec4( vColor, 1. );
}
