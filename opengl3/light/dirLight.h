#pragma once

#include "../shader/shaders.h"

// Support class for adding directional lights to scene.
class DirLight {
public:
    glm::vec3 vColor; // Color of directional light
    glm::vec3 vDirection; // and its direction

    float fAmbient;

    void SetUniformData(ShaderProgram *spProgram, string sLightVarName);

    DirLight();

    DirLight(glm::vec3 vColor, glm::vec3 vDirection, float fAmbient);
};