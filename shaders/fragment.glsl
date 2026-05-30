#version 330

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	if (gl_FragCoord.x < 400) FragColor = vec4(1.0, 0,0,1.0);
	else  FragColor = vec4(0, 1, 0,1);
}

