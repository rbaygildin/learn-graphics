uniform sampler2D colorTexture;

varying vec2 texc;
uniform float shiftY;

uniform float shift;
uniform float kernel[9];
uniform vec2 offset[9];

vec3 apply(in vec2 texcoord)
{
    vec3 res = vec3(0.0);
    for(int i = 0; i < 9; i++){
        res += kernel[i] * texture2D(colorTexture, texc + offset[i]).rgb;
    }
    return res;
}

void main(void)
{
	vec3 texel = apply(texc);
	gl_FragColor = texc.x < shift  ? vec4(texel, 1.0) : texture2D(colorTexture, texc);
}
