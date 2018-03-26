#version 330

smooth in vec2 vTexCoord;
smooth in vec3 vNormal;
smooth in vec4 vEyeSpacePos;
smooth in vec3 vWorldPos;
out vec4 outputColor;

uniform sampler2D gSampler;
uniform vec4 vColor;
uniform bool isFog;
uniform bool isColorMaterial;
uniform vec4 materialColor;

#include "dirLight.frag"
#include "pointLight.frag"
#include "spotLight.frag"

uniform DirectionalLight sunLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

uniform struct FogParameters
{
	vec4 vFogColor; // Fog color
	float fStart; // This is only for linear fog
	float fEnd; // This is only for linear fog
	float fDensity; // For exp and exp2 equation
	int iEquation; // 0 = linear, 1 = exp, 2 = exp2
} fogParams;

float getFogFactor(FogParameters params, float fFogCoord)
{
	float fResult = 0.0;
	if(params.iEquation == 0)
		fResult = (params.fEnd-fFogCoord)/(params.fEnd-params.fStart);
	else if(params.iEquation == 1)
		fResult = exp(-params.fDensity*fFogCoord);
	else if(params.iEquation == 2)
		fResult = exp(-pow(params.fDensity*fFogCoord, 2.0));
		
	fResult = 1.0-clamp(fResult, 0.0, 1.0);
	
	return fResult;
}

void main()
{
	vec3 vNormalized = normalize(vNormal);

	vec4 vTexColor = vec4(1.0, 1.0, 1.0, 1.0);

	if(isColorMaterial){
	    vTexColor = materialColor;
	}
	else{
	    vTexColor = texture(gSampler, vTexCoord);
	}
	vec4 vDirLightColor = getDirectionalLightColor(sunLight, vNormal);
	PointLight pointLightCopy = pointLight;

	pointLightCopy.vPosition = vec3(vEyeSpacePos.x, vEyeSpacePos.y, vEyeSpacePos.z);

	vec4 vPointLightColor = getPointLightColor(pointLightCopy, vWorldPos, vNormal);

	pointLightCopy.vPosition = vec3(vEyeSpacePos.x, vEyeSpacePos.y, vEyeSpacePos.z);
	pointLightCopy.vColor = vec3(1.0, 1.0, 0.0);
	vec4 vPointLightColor2 = getPointLightColor(pointLightCopy, vWorldPos, vNormal);

	vec4 vSpotLightColor = GetSpotLightColor(spotLight, vWorldPos);

	vec4 mixDir = vTexColor * vColor * vDirLightColor;
	vec4 mixPoint = vTexColor * vColor * vPointLightColor;
	vec4 mixPoint2 = vTexColor * vColor * vPointLightColor2;
	vec4 mixSpot = vTexColor * vColor * vSpotLightColor;
	vec4 vMixedColor = clamp(mixDir + mixPoint + mixPoint2, 0.0, 1.0);
	
	float fFogCoord = abs(vEyeSpacePos.z / vEyeSpacePos.w);

	if(isFog){
	    outputColor = mix(vMixedColor, fogParams.vFogColor, getFogFactor(fogParams, fFogCoord));
	}
	else{
	    outputColor = vMixedColor;
	}
}