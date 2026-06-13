#version 330
out vec4 FragColor;

in GS_OUT {
	vec2 texCoords;
}fs_in;

uniform sampler2D texture1;

void main() {
	FragColor = texture(texture1, fs_in.texCoords);
}

