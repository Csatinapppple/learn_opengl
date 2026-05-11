#version 330

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	//FragColor = texture(texture1, TexCoords);
	FragColor = vec4(vec3(gl_FragCoord.z),1);
}

