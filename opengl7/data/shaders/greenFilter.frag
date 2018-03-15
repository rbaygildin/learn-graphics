// текстуры
uniform sampler2D colorTexture;
uniform float shift;

varying vec2 texc;
uniform float shiftY;

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

const float threshold = 0.5;
const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 apply(in vec2 texcoord)
{
    vec3 rgb = texture2D(colorTexture, texcoord).rgb;
    return vec3(0, rgb.g, 0);
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
