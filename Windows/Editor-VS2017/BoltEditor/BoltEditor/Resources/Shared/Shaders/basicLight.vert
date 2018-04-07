// Version du GLSL
#version 330 compatibility

//IN
in vec3 in_Color;

// UNIFORM
uniform vec3 normal;
uniform vec3 ambiantColor;
uniform float ambiantIntensity;
uniform vec3 diffuseColor;
uniform vec3 diffuseDirection;
uniform float diffuseIntensity;

uniform int useDebugColor;
uniform vec3 debugColor;

//OUT
out vec3 vColor;

// Fonction main
void main()
{
	vec3 sampledColor;
	if( useDebugColor == 0 )
	{
		sampledColor = in_Color;
	}
	else
	{
		sampledColor = debugColor;
	}

	vec3 computedAmbiant = ambiantColor * ambiantIntensity;
	float diffuseFactor = dot( normal, -diffuseDirection );
	vec3 computedDiffuse = diffuseColor * diffuseFactor * diffuseIntensity;
	vec3 concatenatedDiffuseAmbiant = ( computedAmbiant + computedDiffuse ) / 2;
	vColor = sampledColor * concatenatedDiffuseAmbiant;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
