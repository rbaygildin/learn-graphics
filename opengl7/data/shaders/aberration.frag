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

//const vec2 offset[9] = vec2[9](
//	vec2(-1.0,-1.0), vec2( 0.0,-1.0), vec2( 1.0,-1.0),
//	vec2(-1.0, 0.0), vec2( 0.0, 0.0), vec2( 1.0, 0.0),
//	vec2(-1.0, 1.0), vec2( 0.0, 1.0), vec2( 1.0, 1.0)
//);

vec3 apply(in vec2 texcoord)
{
//	vec2 pstep = vec2(1.0) / vec2(textureSize(colorTexture, 0));
    vec2 pstep = vec2(1.0) / vec2(128);
	vec4 res  = vec4(0.0);
//
//	for (int i = 0; i < 9; ++i)
//		res += texture2D(colorTexture, texcoord) * kernel[i];
//
//	return vec3(res);
    return vec3(
        texture2D(colorTexture, texcoord + vec2(0.05, 0.0)).r,
        texture2D(colorTexture, texcoord + vec2(0.0, 0.0)).g,
        texture2D(colorTexture, texcoord + vec2(-0.05, 0.0)).b
    );
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
