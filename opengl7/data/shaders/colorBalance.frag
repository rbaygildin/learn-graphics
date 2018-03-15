uniform sampler2D colorTexture;
uniform float redLevel;
uniform float greenLevel;
uniform float blueLevel;
uniform float shift;
uniform float shiftY;

varying vec2 texc;

vec3 apply(in vec2 texcoord)
{
    vec3 rgb = texture2D(colorTexture, texcoord).rgb;
    float r = rgb.r + redLevel;
    float g = rgb.g + greenLevel;
    float b = rgb.b + blueLevel;
    r = r < 0.0 ? 0.0 : r;
    g = g < 0.0 ? 0.0 : g;
    b = b < 0.0 ? 0.0 : b;
    r = r > 1.0 ? 1.0 : r;
    g = g > 1.0 ? 1.0 : g;
    b = b > 1.0 ? 1.0 : b;
    return vec3(r, g, b);
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
