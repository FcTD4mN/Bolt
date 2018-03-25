// Version du GLSL
#version 330 compatibility

//IN
in vec3 in_Color;

//OUT
out vec3 vColor;

// Fonction main
void main()
{
	//vec4 pos = gl_Vertex;
	//vColor = pos.xyz / 20.f;
	vColor = in_Color;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
