#version 120

// varying = input du fragment shader

varying vec3 v_Color;

void main(void)
{
// la couleur finale RGBA (en theorie) du pixel
	gl_FragColor = vec4(v_Color, 1.0);
}