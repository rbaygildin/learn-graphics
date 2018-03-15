uniform sampler2D colorTexture;
uniform float shift;
uniform float shiftY;

varying vec2 texc;

vec3 apply(in vec2 texcoord)
{

    vec2 xy = 2.0 * texcoord + vec2(-1.0);
    xy += vec2(1.5) * sin(3.1459 * xy);
    texcoord = (xy + vec2(1.0)) / vec2(2.0);
    return vec3(texture2D(colorTexture, texcoord).rgb);
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
