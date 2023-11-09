#version 330

#ifdef GL_ES
precision mediump float;
#endif

in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    FragColor = vec4(TexCoords.x, TexCoords.y, 0.5, 1.0);
}
