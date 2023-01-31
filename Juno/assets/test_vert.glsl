#version 450 core

layout(location = 0) in vec3 vertPosition;

void main() {
    gl_Position = vec4(vertPosition.x, vertPosition.y, vertPosition.z, 1.0f);
}