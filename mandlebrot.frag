#version 100
#ifdef GL_ES
precision mediump float;
#endif

varying vec2 TexCoords;

void main() {
    vec2 c = TexCoords * 2.0 - 1.0; // Transform from [0,1] to [-1,1]
    vec2 z = vec2(0.0);
    int n;

    for(int i = 0; i < 100; i++) {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;

        if (dot(z, z) > 4.0) {
            break;
        }
        n = i;
    }

    float color = float(n) / 100.0;
    gl_FragColor = vec4(color, color, color, 1.0);
}
