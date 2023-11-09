#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

uniform float zoom;
uniform vec2 pan;
uniform vec2 resolution;
uniform vec2 c;

in vec2 TexCoords;
out vec4 fragColor;

vec3 getColor(float t) {
    // Define pastel palette
    vec3 a = vec3(0.8, 0.9, 0.8); // light tone
    vec3 b = vec3(0.9, 0.9, 0.9); // medium tone
    vec3 c = vec3(1.0, 1.0, 1.0); // high tone
    vec3 d = vec3(0.00, 0.10, 0.20); // phase shift

    // Use a smooth polynomial for interpolation
    return a + b * cos(6.28318 * (c * t + d));
}

void main() {
    vec2 pos = (TexCoords - 0.5) * zoom - pan;
    int max_iter = 300;
    vec2 z = pos;
    int n;
    for(n = 0; n < max_iter; n++) {
        if(dot(z, z) > 4.0) break;
        z = vec2(z.x*z.x - z.y*z.y, 2.0*z.x*z.y) + c;
    }

    float color = float(n) / float(max_iter);
    color = 1.0 - color;
    color = pow(color, 0.3);
    fragColor = vec4(getColor(color), 1.0);
}

