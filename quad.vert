#version 330

#ifdef GL_ES
    precision mediump float; // This is needed for OpenGL ES, ignored in OpenGL
#endif

in vec2 aPos;
in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
