#version 330

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	if(gl_FrontFacing) FragColor = texture(texture1, TexCoords);
	else FragColor = vec4(1,0,0,1);
}

