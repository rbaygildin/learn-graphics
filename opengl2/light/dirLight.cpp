#include "../common.h"
#include "dirLight.h"

DirLight::DirLight() {
    vColor = glm::vec3(1.0f, 1.0f, 1.0f);
    vDirection = glm::vec3(0.0f, 1.0f, 0.0f);

    fAmbient = 1.0f;
}

DirLight::DirLight(glm::vec3 vColor, glm::vec3 vDirection, float fAmbient) {
    this->vColor = vColor;
    this->vDirection = vDirection;
    this->fAmbient = fAmbient;
}

void DirLight::SetUniformData(ShaderProgram *spProgram, std::string sLightVarName) {
    spProgram->SetUniform(sLightVarName + ".vColor", vColor);
    spProgram->SetUniform(sLightVarName + ".vDirection", vDirection);

    spProgram->SetUniform(sLightVarName + ".fAmbient", fAmbient);
}