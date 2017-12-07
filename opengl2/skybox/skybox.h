#pragma once

#include "../texture/texture.h"
#include "../buf/vertexBufferObject.h"

// Class for using skybox.
class Skybox
{
public:
	void LoadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight, string a_sTop, string a_sBottom);
	void RenderSkybox();

	void DeleteSkybox();
private:
	UINT uiVAO;
	CVertexBufferObject vboRenderData;
	Texture tTextures[6];
	string sDirectory;
	string sFront, sBack, sLeft, sRight, sTop, sBottom;
};