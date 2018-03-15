// текстуры
uniform sampler2D colorTexture;
uniform float shift;

varying vec2 texc;
uniform float time;
uniform float step;

void main(void)
{
    vec2 p = -1.0 + 2.0 * texc;
    float len = length(p);
    vec2 uv = texc + (p/len) * cos(len * 12.0 - time * 4.0) * step;
    vec3 col = texture2D(colorTexture, uv).xyz;
    gl_FragColor = texc.x < shift ? vec4(col, 1.0) : texture2D(colorTexture, texc);
}
