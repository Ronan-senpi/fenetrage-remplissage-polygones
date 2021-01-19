#version 120

// float : 1 seule composante
// vec2 : 2 composantes float
// vec3 : 3 ""  
// vec4 : 4 ""
// struct vec4 { float x, y, z, w };
// SIMD = Single Instruction 
// Multiple Data

// attribute = inputs du vertex shader
attribute vec2 a_Position;
attribute vec3 a_Color;

// varying = output du vertex shader

varying vec3 v_Color;

void main(void)
{
	vec4 a = vec4(1.0, 0.0, -45.0, 1.0);
	vec4 b = vec4(-1.0, 0.0, +45.0, -1.0);
	vec4 c = a + b;

	vec3 d = vec3(c); // c.xyz

	v_Color = a_Color;

// la position 4D (NDC) du sommet
	gl_Position = vec4(a_Position, 0.0, 1.0);
}