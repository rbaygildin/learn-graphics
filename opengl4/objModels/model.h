#pragma once

#include "../common.h"
#include <GL/glew.h>
#include "assimp/scene.h"
#include "assimp/mesh.h"
#include "../texture/texture.h"
#include <vector>

using namespace std;

struct MeshEntry {
    static enum BUFFERS {
        VERTEX_BUFFER, TEXCOORD_BUFFER, NORMAL_BUFFER, INDEX_BUFFER
    };
    GLuint vao;
    GLuint vbo[4];

    unsigned int materialIndex;
    unsigned int elementCount;

    explicit MeshEntry(aiMesh *mesh);

    ~MeshEntry();

    void render();
};

class Mesh {
public :

    vector<MeshEntry *> meshEntries;
    vector<Texture*> textures;

public:
    explicit Mesh(const char *filename);

    ~Mesh();

    void render();
};