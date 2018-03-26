//
// Created by Max Heartfield on 26.03.18.
//

#include "Cube.h"

// Loads skybox and creates VAO and VBO for it.
void Skybox::LoadSkybox(string a_sDirectory, string a_sFront, string a_sBack, string a_sLeft, string a_sRight,
                        string a_sTop, string a_sBottom) {
    tTextures[0].LoadTexture2D(a_sDirectory + a_sFront);
    tTextures[1].LoadTexture2D(a_sDirectory + a_sBack);
    tTextures[2].LoadTexture2D(a_sDirectory + a_sLeft);
    tTextures[3].LoadTexture2D(a_sDirectory + a_sRight);
    tTextures[4].LoadTexture2D(a_sDirectory + a_sTop);
    tTextures[5].LoadTexture2D(a_sDirectory + a_sBottom);

    sDirectory = a_sDirectory;

    sFront = a_sFront;
    sBack = a_sBack;
    sLeft = a_sLeft;
    sRight = a_sRight;
    sTop = a_sTop;
    sBottom = a_sBottom;

    FOR(i, 6) {
        tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR);
        tTextures[i].SetSamplerParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        tTextures[i].SetSamplerParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glGenVertexArrays(1, &uiVAO);
    glBindVertexArray(uiVAO);

    vboRenderData.CreateVBO();
    vboRenderData.BindVBO();

    glm::vec3 vSkyBoxVertices[24] = {
            // Front face
            glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(2.0f, -2.0f, 2.0f), glm::vec3(-2.0f, 2.0f, 2.0f),
            glm::vec3(-2.0f, -2.0f, 2.0f),
            // Back face
            glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(-2.0f, -2.0f, -2.0f), glm::vec3(2.0f, 2.0f, -2.0f),
            glm::vec3(2.0f, -2.0f, -2.0f),
            // Left face
            glm::vec3(-2.0f, 2.0f, 2.0f), glm::vec3(-2.0f, -2.0f, 2.0f), glm::vec3(-2.0f, 2.0f, -2.0f),
            glm::vec3(-2.0f, -2.0f, -2.0f),
            // Right face
            glm::vec3(2.0f, 2.0f, -2.0f), glm::vec3(2.0f, -2.0f, -2.0f), glm::vec3(2.0f, 2.0f, 2.0f),
            glm::vec3(2.0f, -2.0f, 2.0f),
            // Top face
            glm::vec3(-2.0f, 2.0f, -2.0f), glm::vec3(2.0f, 2.0f, -2.0f), glm::vec3(-2.0f, 2.0f, 2.0f),
            glm::vec3(2.0f, 2.0f, 2.0f),
            // Bottom face
            glm::vec3(2.0f, -2.0f, -2.0f), glm::vec3(-2.0f, -2.0f, -2.0f), glm::vec3(2.0f, -2.0f, 2.0f),
            glm::vec3(-2.0f, -2.0f, 2.0f),

    };
    glm::vec2 vSkyBoxTexCoords[4] = {
            glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
    };

    glm::vec3 vSkyBoxNormals[6] = {
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, -1.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f, -1.0f, 0.0f)
    };

    FOR(i, 24) {
        vboRenderData.AddData(&vSkyBoxVertices[i], sizeof(glm::vec3));
        vboRenderData.AddData(&vSkyBoxTexCoords[i % 4], sizeof(glm::vec2));
        vboRenderData.AddData(&vSkyBoxNormals[i / 4], sizeof(glm::vec3));
    }

    vboRenderData.UploadDataToGPU(GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2),
                          (void *) sizeof(glm::vec3));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2),
                          (void *) (sizeof(glm::vec3) + sizeof(glm::vec2)));
}

// Renders skybox.
void Skybox::RenderSkybox() {
    glDepthMask(0);
    glBindVertexArray(uiVAO);
    FOR(i, 6) {
        tTextures[i].BindTexture();
        glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
    }
    glDepthMask(1);
}

// Deletes skybox and all associated memory.
void Skybox::DeleteSkybox() {
    FOR(i, 6)tTextures[i].DeleteTexture();
    glDeleteVertexArrays(1, &uiVAO);
    vboRenderData.DeleteVBO();
}