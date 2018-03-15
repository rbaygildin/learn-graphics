// текстуры
uniform sampler2D colorTexture;
uniform float shift;

varying vec2 texc;

#define KERNEL_SIZE 9

uniform float kernel[9];
uniform vec2 offset[9];

float textureSize;

const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 gray(in vec3 t){
    return vec3(dot(factor, t));
}

vec3 apply(in vec2 texcoord)
{
    vec2 pstep = vec2(1.0) / vec2(128);
	vec3 res  = vec3(0.0);
    res += gray(texture2D(colorTexture, texcoord + vec2(1.0, -1.0) * pstep).rgb);
    res += gray(texture2D(colorTexture, texcoord + vec2(-1.0, 0.0) * pstep).rgb);
    res -= 4.0 * gray(texture2D(colorTexture, texcoord + vec2(1.0, -1.0) * pstep).rgb);
    res += gray(texture2D(colorTexture, texcoord + vec2(1.0, 0.0) * pstep).rgb);
    res += gray(texture2D(colorTexture, texcoord + vec2(0.0, 1.0) * pstep).rgb);
    return vec3(res);
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}