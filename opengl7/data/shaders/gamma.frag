// текстуры
uniform sampler2D colorTexture;
uniform float gamma;
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
    return vec3(pow(texture2D(colorTexture, texcoord).rgb, vec3(1.0 / gamma)));
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
