// Version du GLSL
#version 330 compatibility

//IN
in vec3 in_Color;

// UNIFORM
uniform vec3 normal;
uniform vec3 lightDirection;

//OUT
out vec3 vColor;

// Fonction main
void main()
{
	//vec4 pos = gl_Vertex;
	//vColor = pos.xyz / 20.f;
	float diffuseFactor = dot( normal, -lightDirection );
	vColor = in_Color * diffuseFactor;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
