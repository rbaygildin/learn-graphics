//
// Created by Max Heartfield on 06.12.17.
//

#ifndef OPENGL2_APP_H
#define OPENGL2_APP_H
/**
 * © Roman Yarnykh, 2017
 */

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


#define NUMTEXTURES 7

/**
 * Main Application context, rendering
 */
class App {

public funcs:

    App() = default;

    static void start(int argc, char **argv);

    static void destroy();

    static void render();

private funcs:

    static void initScene();

    static void keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods);

    static void posCallback(GLFWwindow *window, double xPos, double yPos);

    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);

    static void resizeCallback(GLFWwindow *window, int width, int height);

private fields:
    static GLFWwindow *wnd;
    static CVertexBufferObject vboSceneObjects, vboCubeInd, vboCube, vboCylinder;
    static UINT uiVAOs[2];
    static Texture tTextures[NUMTEXTURES];
    static FlyingCamera cCamera;
    static Skybox sbMainSkybox;
    static DirLight dlSun;
    static float fGlobalAngle;
    static float fTextureContribution;
    static bool isRotating;
};


#endif //OPENGL2_APP_H
