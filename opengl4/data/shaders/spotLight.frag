#version 330

#include_part

struct SpotLight
{
	vec3 vColor;
  vec3 vPosition;
	vec3 vDirection;
  
  // Used as boolean, whether spotlight is on
  int bOn;

  // If cone angle is set from program, we also provide its cosine,
  // so that it isn't always recalculated
	float fConeAngle, fConeCosine;
  
  // Only linear attenuation, you can code const and exp as well
  float fLinearAtt;
};

vec4 GetSpotLightColor(const SpotLight spotLight, vec3 vWorldPos);

#definition_part

vec4 GetSpotLightColor(const SpotLight spotLight, vec3 vWorldPos)
{
  // If flashlight isn't turned on, return no color
  if(spotLight.bOn == 0)return vec4(0.0, 0.0, 0.0, 0.0);
  // Distance from fragment's position
	float fDistance = distance(vWorldPos, spotLight.vPosition);
  
  // Get direction vector to fragment
  vec3 vDir = vWorldPos-spotLight.vPosition;
  vDir = normalize(vDir);
  
  // Cosine between spotlight direction and directional vector to fragment
  float fCosine = dot(spotLight.vDirection, vDir);
  
  // Difference between max cosine and current cosine
  float fDif = 1.0-spotLight.fConeCosine;
  
  // This is how strong light is depending whether its nearer to the center of
  // cone or nearer to its borders (onway factor in article), clamp to 0.0 and 1.0
  float fFactor = clamp((fCosine-spotLight.fConeCosine)/fDif, 0.0, 1.0);
    
  // If we're inside cone, calculate color
  if(fCosine > spotLight.fConeCosine)
    return vec4(spotLight.vColor, 1.0)*fFactor/(fDistance*spotLight.fLinearAtt);
  
  // No color otherwise
  return vec4(0.0, 0.0, 0.0, 0.0);
}