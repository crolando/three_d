#version 330

#ifdef GL_ES
precision mediump float;
#endif

uniform float zoom;
uniform vec2 pan;
uniform vec2 resolution;

in vec2 TexCoords;
out vec4 fragColor;

void main()
{
    vec2 pos = (TexCoords - vec2(0.5, 0.5)) * zoom - pan;
    
    int max_iter = 300;
    vec2 c = pos;
    vec2 z = vec2(0.0, 0.0);
    int n;
    for(n = 0; n < max_iter; n++)
    {
        if(dot(z, z) > 4.0) break;
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
    }
    
    float color = float(n) / float(max_iter);
    color = 1.0 - color;
    color = pow(color, 0.3); // gamma correction
    
    fragColor = vec4(vec3(color), 1.0);
}

