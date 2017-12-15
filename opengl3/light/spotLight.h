#pragma once

#include "../shader/shaders.h"

// Support class for adding spotlights to scene.
class SpotLight {
public:
    glm::vec3 vColor;
    glm::vec3 vPosition;
    glm::vec3 vDirection;

    int bOn;
    float fConeAngle;
    float fLinearAtt;

    void SetUniformData(ShaderProgram *spProgram, string sLightVarName);

    SpotLight();

    SpotLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, glm::vec3 a_vDirection, int a_bOn, float a_fConeAngle,
              float a_fLinearAtt);

private:
    // This shouldn't be changed from outside
    float fConeCosine;
};