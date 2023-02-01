#version 450 core

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TextureCoord;

layout(binding = 0) uniform ObjectData {
    mat4 modelMatrix;
};

layout(binding = 1) uniform SceneData {
    mat4 viewMatrix;
    mat4 projectionMatrix;
};

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPosition, 1.0);
    v_TextureCoord = textureCoord;
    // v_Color = modelMatrix;
}