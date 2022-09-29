@Stage Vertex
#version 450 core

layout (location = 0) in vec3 APosition;

void main() {
    gl_Position = vec4(APosition.xyz, 1.0);
}

@Stage Pixel
#version 450 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}