uniform sampler2D colorTexture;
uniform float shift;
varying vec4 color;
varying vec2 texc;
uniform float shiftY;

const vec3 factor = vec3(0.27, 0.67, 0.06);

vec3 apply(in vec2 texcoord)
{
	return vec3(dot(factor, texture2D(colorTexture, texcoord).rgb));
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
