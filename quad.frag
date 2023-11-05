#version 100
#ifdef GL_ES
precision mediump float;
#endif

varying vec2 TexCoords;

void main()
{
    gl_FragColor = vec4(TexCoords.x, TexCoords.y, 0.5, 1.0);
}
