#pragma warning(disable:4996)

#include "common.h"

#include "objModel.h"

CObjModel::CObjModel()
{
	bLoaded = false;
	iAttrBitField = 0;
}

//  Splits string according to some substring and returns it as a vector.
// s - string to split
// t - string to split according to
vector<string> split(string s, string t)
{
	vector<string> res;
	while(1)
	{
		int pos = s.find(t);
		if(pos == -1){res.push_back(s); break;}
		res.push_back(s.substr(0, pos));
		s = s.substr(pos+1, ESZ(s)-pos-1);
	}
	return res;

}

// Returns path of a directory from file path.
string GetDirectoryPath(string sFilePath)
{
	// Get directory path
	string sDirectory = "";
	RFOR(i, ESZ(sFilePath)-1)if(sFilePath[i] == '\\' || sFilePath[i] == '/')
	{
		sDirectory = sFilePath.substr(0, i+1);
		break;
	}
	return sDirectory;
}

// Loads obj model.
//sFileName - full path mode file name
//sMtlFileName - relative path material file
bool CObjModel::LoadModel(string sFileName, string sMtlFileName)
{
	FILE* fp = fopen(sFileName.c_str(), "rt");

	if(fp == NULL)return false;

	char line[255];

	vector<glm::vec3> vVertices;
	vector<glm::vec2> vTexCoords;
	vector<glm::vec3> vNormals;

	iNumFaces = 0;

	while(fgets(line, 255, fp))
	{
		// Error flag, that can be set when something is inconsistent throughout
		// data parsing
		bool bError = false;

		// If it's an empty line, then skip
		if(strlen(line) <= 1)
			continue;

		// Now we're going to process line
		stringstream ss(line);
		string sType;
		ss >> sType;
		// If it's a comment, skip it
		if(sType == "#")
			continue;
		// Vertex
		else if(sType == "v")
		{
			glm::vec3 vNewVertex;
			int dim = 0;
			while(dim < 3 && ss >> vNewVertex[dim])dim++;
			vVertices.push_back(vNewVertex);
			iAttrBitField |= 1;
		}
		// Texture coordinate
		else if(sType == "vt")
		{
			glm::vec2 vNewCoord;
			int dim = 0;
			while(dim < 2 && ss >> vNewCoord[dim])dim++;
			vTexCoords.push_back(vNewCoord);
			iAttrBitField |= 2;
		}
		// Normal
		else if(sType == "vn")
		{
			glm::vec3 vNewNormal;
			int dim = 0;
			while(dim < 3 && ss >> vNewNormal[dim])dim++;
			vNewNormal = glm::normalize(vNewNormal);
			vNormals.push_back(vNewNormal);
			iAttrBitField |= 4;
		}
		// Face definition
		else if(sType == "f")
		{
			string sFaceData;
			// This will run for as many vertex definitions as the face has
			// (for triangle, it's 3)
			while(ss >> sFaceData)
			{
				vector<string> data = split(sFaceData, "/");
				int iVertIndex = -1, iTexCoordIndex = -1, iNormalIndex = -1;
			
				// If there were some vertices defined earlier
				if(iAttrBitField&1)
				{
					if(ESZ(data[0]) > 0)sscanf(data[0].c_str(), "%d", &iVertIndex);
					else bError = true;
				}
				// If there were some texture coordinates defined earlier
				if(iAttrBitField&2 && !bError)
				{
					if(ESZ(data) >= 1)
					{
						// Just a check whether face format isn't f v//vn
						// In that case, data[1] is empty string
						if(ESZ(data[1]) > 0)sscanf(data[1].c_str(), "%d", &iTexCoordIndex);
						else bError = true;
					}
					else bError = true;
				}
				// If there were some normals defined defined earlier
				if(iAttrBitField&4 && !bError)
				{
					if(ESZ(data) >= 2)
					{
						if(ESZ(data[2]) > 0)sscanf(data[2].c_str(), "%d", &iNormalIndex);
						else bError = true;
					}
					else bError = true;
				}
				if(bError)
				{
					fclose(fp);
					return false;
				}
			
				// Check whether vertex index is within boundaries (indexed from 1)
				if(iVertIndex > 0 && iVertIndex <= ESZ(vVertices))
					vboModelData.AddData(&vVertices[iVertIndex-1], sizeof(glm::vec3));
				if(iTexCoordIndex > 0 && iTexCoordIndex <= ESZ(vTexCoords))
					vboModelData.AddData(&vTexCoords[iTexCoordIndex-1], sizeof(glm::vec2));
				if(iNormalIndex > 0 && iNormalIndex <= ESZ(vNormals))
					vboModelData.AddData(&vNormals[iNormalIndex-1], sizeof(glm::vec3));
			}
			iNumFaces++;
		}
		// Shading model, for now just skip it
		else if(sType == "s")
		{
			// Do nothing for now
		}
		// Material specified, skip it again
		else if(sType == "usemtl")
		{
			// Do nothing for now
		}
	}

	fclose(fp);

	if(iAttrBitField == 0)
		return false;

	// Create VBO

	vboModelData.CreateVBO();
	vboModelData.BindVBO();

	vboModelData.UploadDataToGPU(GL_STATIC_DRAW);

	// Create one VAO

	glGenVertexArrays(1, &uiVAO); 
	glBindVertexArray(uiVAO);
	int iDataStride = 0;
	if(iAttrBitField&1)iDataStride += sizeof(glm::vec3);
	if(iAttrBitField&2)iDataStride += sizeof(glm::vec2);
	if(iAttrBitField&4)iDataStride += sizeof(glm::vec3);

	if(iAttrBitField&1)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, iDataStride, 0);
	}
	// Texture coordinates
	if(iAttrBitField&2)
	{
		glEnableVertexAttribArray(1);
		int iDataOffset = 0;
		if(iAttrBitField&1)iDataOffset += sizeof(glm::vec3);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, iDataStride, (void*)iDataOffset);
	}
	// Normal vectors
	if(iAttrBitField&4)
	{
		glEnableVertexAttribArray(2);
		int iDataOffset = 0;
		if(iAttrBitField&1)iDataOffset += sizeof(glm::vec3);
		if(iAttrBitField&2)iDataOffset += sizeof(glm::vec2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, iDataStride, (void*)iDataOffset);
	}
	bLoaded = true;

	// Material should be in the same directory as model
	if(iAttrBitField&2)
	LoadMaterial(GetDirectoryPath(sFileName)+sMtlFileName);

	return true;
}

// Renders model.
void CObjModel::RenderModel()
{
	if(!bLoaded)return;
	glBindVertexArray(uiVAO);
	tAmbientTexture.BindTexture();
	glDrawArrays(GL_TRIANGLES, 0, iNumFaces*3);
}

// sFullMtlFileName - full path to material file
// Loads material (currently only ambient texture).
bool CObjModel::LoadMaterial(string sFullMtlFileName)
{
	// For now, we'll just look for ambient texture, i.e. line that begins with map_Ka
	FILE* fp = fopen(sFullMtlFileName.c_str(), "rt");

	if(fp == NULL)return false;

	char line[255];

	while(fgets(line, 255, fp))
	{
		stringstream ss(line);
		string sType;
		ss >> sType;
		if(sType == "map_Ka")
		{
			string sLine = line;
			// Take the rest of line as texture name, remove newline character from end
			int from = sLine.find("map_Ka")+6+1;
			string sTextureName = sLine.substr(from, ESZ(sLine)-from-1);
			// Texture should be in the same directory as material
			tAmbientTexture.LoadTexture2D(GetDirectoryPath(sFullMtlFileName)+sTextureName, true);
			tAmbientTexture.SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_NEAREST_MIPMAP);
			break;
		}
	}
	fclose(fp);

	return true;
}

// Frees all used resources by model.
void CObjModel::DeleteModel()
{
	if(!bLoaded)return;
	tAmbientTexture.DeleteTexture();
	glDeleteVertexArrays(1, &uiVAO);
	vboModelData.DeleteVBO();
	bLoaded = false;
}

// Returns model polygon count.
int CObjModel::GetPolygonCount()
{
	return iNumFaces;
}