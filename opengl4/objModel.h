#pragma once

#include "texture/texture.h"
#include "objModel.h"
#include "buf/vbo.h"

// Class for handling obj model files.
class CObjModel
{
public:
	bool LoadModel(string sFileName, string sMtlFileName);
	void RenderModel(bool useInnerTexture = true);
	void DeleteModel();

	int GetPolygonCount();

	CObjModel();
private:
	bool bLoaded;
	int iAttrBitField;
	int iNumFaces;

	bool LoadMaterial(string sFullMtlFileName);

	VertexBufferObject vboModelData;
	UINT uiVAO;
	Texture tAmbientTexture;
};