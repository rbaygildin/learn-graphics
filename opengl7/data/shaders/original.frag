// текстуры
uniform sampler2D colorTexture;
uniform float shift;

varying vec2 texc;


void main(void)
{
	gl_FragColor = vec4(texture2D(colorTexture, texc).rgb, 1.0);
}
