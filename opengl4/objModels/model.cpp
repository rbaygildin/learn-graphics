#include "../objModels/model.h"

#include "assimp/Importer.hpp"
#include <boost/filesystem/path.hpp>
#include <algorithm>
#include <string>

using namespace std;

/**
*	Constructor, loading the specified aiMesh
**/
MeshEntry::MeshEntry(aiMesh *mesh) {
    vbo[VERTEX_BUFFER] = NULL;
    vbo[TEXCOORD_BUFFER] = NULL;
    vbo[NORMAL_BUFFER] = NULL;
    vbo[INDEX_BUFFER] = NULL;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    elementCount = mesh->mNumFaces * 3;
    materialIndex = mesh->mMaterialIndex;

    if (mesh->HasPositions()) {
        float *vertices = new float[mesh->mNumVertices * 3];
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            vertices[i * 3] = mesh->mVertices[i].x;
            vertices[i * 3 + 1] = mesh->mVertices[i].y;
            vertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        glGenBuffers(1, &vbo[VERTEX_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        delete[] vertices;
    }


    if (mesh->HasTextureCoords(0)) {
        float *texCoords = new float[mesh->mNumVertices * 2];
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
            texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
        }

        glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 2 * mesh->mNumVertices * sizeof(GLfloat), texCoords, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(1);

        delete[] texCoords;
    }


    if (mesh->HasNormals()) {
        float *normals = new float[mesh->mNumVertices * 3];
        for (int i = 0; i < mesh->mNumVertices; ++i) {
            normals[i * 3] = mesh->mNormals[i].x;
            normals[i * 3 + 1] = mesh->mNormals[i].y;
            normals[i * 3 + 2] = mesh->mNormals[i].z;
        }

        glGenBuffers(1, &vbo[NORMAL_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), normals, GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(2);

        delete[] normals;
    }

    if (mesh->HasFaces()) {
        unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];
        for (int i = 0; i < mesh->mNumFaces; ++i) {
            indices[i * 3] = mesh->mFaces[i].mIndices[0];
            indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
            indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
        }

        glGenBuffers(1, &vbo[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * mesh->mNumFaces * sizeof(GLuint), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(3);

        delete[] indices;
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/**
*	Deletes the allocated OpenGL buffers
**/
MeshEntry::~MeshEntry() {
    if (vbo[VERTEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
    }

    if (vbo[TEXCOORD_BUFFER]) {
        glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
    }

    if (vbo[NORMAL_BUFFER]) {
        glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
    }

    if (vbo[INDEX_BUFFER]) {
        glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
    }

    glDeleteVertexArrays(1, &vao);
}

/**
*	Renders this MeshEntry
**/
void MeshEntry::render() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

/**
*	Mesh constructor, loads the specified filename if supported by Assimp
**/
Mesh::Mesh(const char *filename) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, 0);
    if (!scene) {
        printf("Unable to load mesh: %s\n", importer.GetErrorString());
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        meshEntries.push_back(new MeshEntry(scene->mMeshes[i]));
    }


    for (unsigned int i = 0; i < scene->mNumMaterials; i++) {
        const aiMaterial *pMaterial = scene->mMaterials[i];
        auto texture = new Texture();
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, nullptr, nullptr, nullptr, nullptr, nullptr) ==
                AI_SUCCESS) {
                string FullPath = boost::filesystem::path(filename).parent_path().string() + "/" + string(Path.data);
                texture->LoadTexture2D(FullPath);
                textures.push_back(texture);
            }
        }
    }
}

/**
*	Clears all loaded MeshEntries
**/
Mesh::~Mesh() {
    for (int i = 0; i < meshEntries.size(); ++i) {
        delete meshEntries.at(static_cast<unsigned long>(i));
    }
    meshEntries.clear();
}

/**
*	Renders all loaded MeshEntries
**/
void Mesh::render() {
    for (int i = 0; i < meshEntries.size(); ++i) {
        const unsigned int MaterialIndex = meshEntries[i]->materialIndex;

        if (MaterialIndex < textures.size() && textures[MaterialIndex]) {
            textures[MaterialIndex]->BindTexture(0);
        }
        meshEntries.at(static_cast<unsigned long>(i))->render();
    }
}