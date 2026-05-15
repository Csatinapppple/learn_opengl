#version 330

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	vec4 texColor = texture(texture1, TexCoords);
	FragColor = texColor;
}

