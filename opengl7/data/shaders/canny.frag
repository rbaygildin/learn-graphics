uniform sampler2D colorTexture;
uniform float shift;
uniform float threshold;
uniform float shiftY;

varying vec2 texc;

#define KERNEL_SIZE 9

uniform float kernel[9];
uniform vec2 offset[9];

float textureSize;

const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 gray(in vec3 t){
    return vec3(dot(factor, t));
}

vec3 gaussian(in vec2 coord, in sampler2D t){
    vec3 res = vec3(0);
    vec2 pstep = vec2(1.0) / vec2(128);
    res += texture2D(t, coord + vec2(-1.0, -1.0) * pstep).rgb;
    res += 2.0 * texture2D(t, coord + vec2(0.0, -1.0) * pstep).rgb;
    res += texture2D(t, coord + vec2(1.0, -1.0) * pstep).rgb;

    res += 2.0 * texture2D(t, coord + vec2(-1.0, 0.0) * pstep).rgb;
    res += 4.0 * texture2D(t, coord + vec2(0.0, 0.0) * pstep).rgb;
    res += 2.0 * texture2D(t, coord + vec2(1.0, 0.0) * pstep).rgb;

    res += texture2D(t, coord + vec2(-1.0, 1.0) * pstep).rgb;
    res += 2.0 * texture2D(t, coord + vec2(0.0, 1.0) * pstep).rgb;
    res += texture2D(t, coord + vec2(1.0, 1.0) * pstep).rgb;
    res /= vec3(16.0);
    return res;
}

vec3 sobel_x(in vec2 coord, in sampler2D t){
    vec3 res = vec3(0);
    vec2 pstep = vec2(1.0) / vec2(128);
    res -= gray(texture2D(t, coord + vec2(-1.0, -1.0) * pstep).rgb);
    res += gray(texture2D(t, coord + vec2(1.0, -1.0) * pstep).rgb);
    res -= 2.0 * gray(texture2D(t, coord + vec2(-1.0, 0.0) * pstep).rgb);
    res += 2.0 * texture2D(t, coord + vec2(1.0, 0.0) * pstep).rgb;
    res -= gray(texture2D(t, coord + vec2(-1.0, 1.0) * pstep).rgb);
    res += gray(texture2D(t, coord + vec2(1.0, 1.0) * pstep).rgb);
    return res;
}

vec3 sobel_y(in vec2 coord, in sampler2D t){
    vec3 res = vec3(0);
    vec2 pstep = vec2(1.0) / vec2(128);
    res -= gray(texture2D(t, coord + vec2(-1.0, -1.0) * pstep).rgb);
    res -= 2.0 * gray(texture2D(t, coord + vec2(0.0, -1.0) * pstep).rgb);
    res -= 1.0 * gray(texture2D(t, coord + vec2(1.0, -1.0) * pstep).rgb);

    res += gray(texture2D(t, coord + vec2(-1.0, 0.0) * pstep).rgb);
    res += 2.0 * gray(texture2D(t, coord + vec2(0.0, 1.0) * pstep).rgb);
    res += gray(texture2D(t, coord + vec2(1.0, 1.0) * pstep).rgb);
    return res;
}

vec3 apply(in vec2 coord, in sampler2D t){
    vec3 x = sobel_x(coord, t);
    vec3 y = sobel_y(coord, t);
    vec3 val = sqrt(x*x + y*y);
    vec3 inp = gray(texture2D(t, coord).rgb);
    float r = inp.r;
    float g = inp.g;
    float b = inp.b;
    r = val.x > threshold ? 1.0 : 0.0;
    g = val.y > threshold ? 1.0 : 0.0;
    b = val.z > threshold ? 1.0 : 0.0;
    return gray(vec3(r, g, b));
}


void main(void)
{
	vec3 texel = apply(texc, colorTexture);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
