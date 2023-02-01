#version 450 core

in vec2 v_TextureCoord;
// in vec4 v_Color;

out vec4 fragColor;

uniform sampler2D u_Texture;

void main() {
    // fragColor = vec4(v_TextureCoord.x, v_TextureCoord.y, 0.0, 1.0);
    fragColor = texture(u_Texture, v_TextureCoord);
    // fragColor = v_Color;
}