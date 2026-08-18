#version 330

uniform sampler2DMS screenTextureMS;
in vec2 TexCoords;
out vec4 FragColor;

void main() {

    // Access individual samples
    vec4 sample0 = texelFetch(screenTextureMS, ivec2(gl_FragCoord.xy), 0);
    vec4 sample1 = texelFetch(screenTextureMS, ivec2(gl_FragCoord.xy), 1);
    vec4 sample2 = texelFetch(screenTextureMS, ivec2(gl_FragCoord.xy), 2);
    vec4 sample3 = texelFetch(screenTextureMS, ivec2(gl_FragCoord.xy), 3);
    
    // Standard averaging (basic MSAA resolve)
    FragColor = (sample0 + sample1 + sample2 + sample3) / 4.0;
}
