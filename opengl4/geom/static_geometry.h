#pragma once

#include "../buf/vbo.h"

extern glm::vec3 vCubeVertices[36];
//extern glm::vec3 vCubeVertices2[24];
extern glm::vec3 vCubeVertices2[8];
extern unsigned int iCubeindices[36];
extern glm::vec2 vCubeTexCoords[6];
extern glm::vec3 vCubeNormals[6];
extern glm::vec3 vGround[6];

int GenerateTorus(VertexBufferObject &vboDest, float fRadius, float fTubeRadius, int iSubDivAround, int iSubDivTube);
int GenerateCylinder(VertexBufferObject &vboDest, float fRadius, float fHeight, int iSubDivAround, float fMapU = 1.0f, float fMapV = 1.0f);
void AddSceneObjects(VertexBufferObject& vboDest);
void AddCube(VertexBufferObject& vboDest);
extern int iTorusFaces, iTorusFaces2, iCylinder;