#include "../common.h"
#include "dirLight.h"

DirLight::DirLight() {
    color = glm::vec3(1.0f, 1.0f, 1.0f);
    vDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    ambient = 1.0f;
}

DirLight::DirLight(glm::vec3 vColor, glm::vec3 vDirection, float fAmbient) {
    this->color = vColor;
    this->vDirection = vDirection;
    this->ambient = fAmbient;
}

void DirLight::SetUniformData(ShaderProgram *spProgram, std::string sLightVarName) {
    spProgram->SetUniform(sLightVarName + ".vColor", color);
    spProgram->SetUniform(sLightVarName + ".vDirection", vDirection);

    spProgram->SetUniform(sLightVarName + ".fAmbient", ambient);
}