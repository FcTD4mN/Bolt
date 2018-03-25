// Version du GLSL
#version 330 compatibility

//IN
in vec3 in_Color;

// UNIFORM
uniform vec3 normal;

//OUT
out vec3 vColor;

// Fonction main
void main()
{
	vColor = in_Color;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
