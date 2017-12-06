//
// Created by Max Heartfield on 06.12.17.
//

#ifndef OPENGL2_APP_H
#define OPENGL2_APP_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"
#include "logger.h"
#include "shader/shaders.h"
#include "texture/texture.h"
#include "buf/vertexBufferObject.h"
#include "camera/flyingCamera.h"
#include "skybox/skybox.h"
#include "light/dirLight.h"
#include "geom/static_geometry.h"


#define NUMTEXTURES 5

class App {

public funcs:

    static void start(int argc, char **argv);

    static void destroy();

    static void render();

private funcs:

    static void initScene();

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xPos, double yPos);

private fields:
    static GLFWwindow *wnd;
    static CVertexBufferObject vboSceneObjects, vboCubeInd, vboCube;
    static UINT uiVAOs[2];
    static CTexture tTextures[NUMTEXTURES];
    static CFlyingCamera cCamera;
    static CSkybox sbMainSkybox;
    static CDirectionalLight dlSun;
    static float fGlobalAngle;
    static float fTextureContribution;
};


#endif //OPENGL2_APP_H
