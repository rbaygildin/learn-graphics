#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec3 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSamplers[2];
uniform float fTextureContributions[2];
uniform vec4 vColor;
uniform int numTextures;

#include "dirLight.frag"

uniform DirectionalLight sunLight;

void main()
{
	vec3 vNormalized = normalize(vNormal);
	
	vec4 vTexColor1 = texture2D(gSamplers[0], vTexCoord);
	vec4 vTexColor2 = texture2D(gSamplers[1], vTexCoord);
	vec4 vMixedTexColor = vTexColor1*fTextureContributions[0];
	if (numTextures > 1)
		 vMixedTexColor += vTexColor2*fTextureContributions[1];
	vec4 vDirLightColor = getDirectionalLightColor(sunLight, vNormal);
	outputColor = vColor*vMixedTexColor*vDirLightColor;
}