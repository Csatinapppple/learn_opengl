#version 330

in VS_OUT{
	vec2 TexCoords;
} fs_in;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
	if(gl_FrontFacing) FragColor = texture(texture1, fs_in.TexCoords);
	else FragColor = vec4(1,0,0,1);
}

