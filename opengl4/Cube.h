//
// Created by Max Heartfield on 26.03.18.
//
#ifndef OPENGL4_CUBE_H
#define OPENGL4_CUBE_H

#include "texture/texture.h"
#include "buf/vbo.h"
#include "common.h"

// Class for using skybox.
class Skybox
{
public:
    void LoadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom);
    void RenderSkybox();

    void DeleteSkybox();
private:
    UINT uiVAO;
    VertexBufferObject vboRenderData;
    Texture tTextures[6];
    string sDirectory;
    string sFront, sBack, sLeft, sRight, sTop, sBottom;
};

#endif //OPENGL4_CUBE_H
