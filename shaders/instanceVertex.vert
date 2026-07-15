#version 330
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 instanceModel;

uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;

void main() {
	gl_Position = projection * view * instanceModel * vec4(aPos, 1);
	TexCoord = aTexCoord;
}
