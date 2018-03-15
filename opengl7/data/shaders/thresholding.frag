// текстуры
uniform float shift;
uniform sampler2D colorTexture;
uniform float threshold;

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


const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 apply(in vec2 texcoord)
{
    vec3 rgb = texture2D(colorTexture, texcoord).rgb;
    float r = rgb.r;
    float g = rgb.g;
    float b = rgb.b;

    r = rgb.r > threshold ? r : 0.0;
    g = rgb.g > threshold ? g : 0.0;
    b = rgb.b > threshold ? b : 0.0;
    return vec3(dot(factor, vec3(r, g, b)));
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
