attribute vec4 vertex;
attribute vec2 texCoord;
varying vec2 texc;
uniform mat4 matrix;
uniform float threshold;
uniform float gamma;
uniform float shift;
uniform float time;
uniform float step;

void main(void)
{
    gl_Position = matrix * vertex;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    texc = texCoord;
}


