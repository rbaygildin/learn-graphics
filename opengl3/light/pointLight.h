#pragma once

#include "../shader/shaders.h"

// Support class for adding point lights to scene.
class PointLight
{
public:
	glm::vec3 vColor; // Color of point light
	glm::vec3 vPosition; // and position

	float fAmbient;

	float fConstantAtt;
	float fLinearAtt;
	float fExpAtt;

	void SetUniformData(ShaderProgram* spProgram, string sLightVarName);

	PointLight();
	PointLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, float a_fAmbient, float a_fConstantAtt, float a_fLinearAtt, float a_fExpAtt);
};