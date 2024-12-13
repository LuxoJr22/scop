#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in float transition;
layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    vec4 face = vec4(fragColor.x, fragColor.x, fragColor.x, 1);
    vec4 text =  texture(texSampler, fragTexCoord);
    outColor = mix(face, text, transition);
}