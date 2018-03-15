// текстуры
uniform sampler2D colorTexture;
uniform float shift;
uniform float shiftY;

varying vec2 texc;

// Ядро свертки
#define KERNEL_SIZE 9

uniform float kernel[9];
uniform vec2 offset[9];

float textureSize;
const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 apply(in vec2 texcoord)
{

    vec2 pstep = vec2(1.0) / vec2(128);
	vec4 res  = vec4(0.0);
//    res -= texture2D(colorTexture, texcoord + vec2(-1.0, -1.0) * pstep);
//    res -= texture2D(colorTexture, texcoord + vec2(0.0, 0.0) * pstep);
//    res += texture2D(colorTexture, texcoord + vec2(1.0, 1.0) * pstep) * 2.0;


//    res -= 2.0 * texture2D(colorTexture, texcoord + vec2(-1.0, -1.0) * pstep);
//    res -= texture2D(colorTexture, texcoord + vec2(0.0, -1.0) * pstep);
//    res -= texture2D(colorTexture, texcoord + vec2(-1.0, 0.0) * pstep);
//    res += texture2D(colorTexture, texcoord + vec2(0.0, 0.0) * pstep);
//    res += texture2D(colorTexture, texcoord + vec2(1.0, 0.0) * pstep);
//    res += texture2D(colorTexture, texcoord + vec2(0.0, 1.0) * pstep);
//    res += 2.0 * texture2D(colorTexture, texcoord + vec2(1.0, 1.0) * pstep);

        res -= 2.0 * texture2D(colorTexture, texcoord + vec2(-1.0, -1.0) * pstep);
        res -= texture2D(colorTexture, texcoord + vec2(0.0, -1.0) * pstep);
        res -= texture2D(colorTexture, texcoord + vec2(-1.0, 0.0) * pstep);
        res += texture2D(colorTexture, texcoord + vec2(0.0, 0.0) * pstep);
        res += texture2D(colorTexture, texcoord + vec2(1.0, 0.0) * pstep);
        res += texture2D(colorTexture, texcoord + vec2(0.0, 1.0) * pstep);
        res += 2.0 * texture2D(colorTexture, texcoord + vec2(1.0, 1.0) * pstep);
    return vec3(dot(factor, res.rgb));
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
