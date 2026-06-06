#version 330
out vec4 FragColor;

in GS_OUT {
	vec3 fragColor;
}fs_in;

void main() {
	FragColor = vec4(fs_in.fragColor, 1.0);
}

