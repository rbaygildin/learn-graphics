#include "../common.h"

#include "spotLight.h"

SpotLight::SpotLight() {
    vColor = glm::vec3(1.0f, 1.0f, 1.0f);
    vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    vDirection = glm::vec3(0.0f, 0.0f, -1.0f);

    bOn = 1;
    fConeAngle = 20.0f;
    fLinearAtt = 0.02f;
}

SpotLight::SpotLight(glm::vec3 a_vColor, glm::vec3 a_vPosition, glm::vec3 a_vDirection, int a_bOn, float a_fConeAngle,
                     float a_fLinearAtt) {
    vColor = a_vColor;
    vPosition = a_vPosition;
    vDirection = a_vDirection;

    bOn = a_bOn;
    fConeAngle = a_fConeAngle;
    fLinearAtt = a_fLinearAtt;
}

// Sets all spot light data.
// spProgram - shader program
// sLightVarName - name of spot light variable
void SpotLight::SetUniformData(ShaderProgram *spProgram, string sLightVarName) {
    spProgram->SetUniform(sLightVarName + ".vColor", vColor);
    spProgram->SetUniform(sLightVarName + ".vPosition", vPosition);
    spProgram->SetUniform(sLightVarName + ".vDirection", vDirection);

    spProgram->SetUniform(sLightVarName + ".bOn", bOn);
    spProgram->SetUniform(sLightVarName + ".fConeAngle", fConeAngle);
    spProgram->SetUniform(sLightVarName + ".fConeCosine", cos(fConeAngle * 3.1415f / 180.0f));
    spProgram->SetUniform(sLightVarName + ".fLinearAtt", fLinearAtt);
}

