uniform sampler2D colorTexture;
uniform float shift;

varying vec2 texc;

const vec3 factor     = vec3(0.27, 0.67, 0.06);
const vec3 darkColor  = vec3(0.2, 0.05, 0.0);
const vec3 lightColor = vec3(1.0,  0.9, 0.5);

vec3 apply(in vec2 texcoord)
{
     return mix(darkColor, lightColor,
            dot(factor, texture2D(colorTexture, texcoord).rgb));
}

void main(void)
{
	vec3 texel = apply(texc);

	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
