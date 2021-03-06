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

#include "objModels/model.h"
#include "common.h"
#include "logger.h"
#include "shader/shaders.h"
#include "texture/texture.h"
#include "buf/vbo.h"
#include "camera/flyingCamera.h"
#include "skybox/skybox.h"
#include "light/dirLight.h"
#include "geom/static_geometry.h"
#include "light/spotLight.h"
#include "light/pointLight.h"
#include "objModel.h"

#define NUMTEXTURES 5
#define FOG_EQUATION_LINEAR        0
#define FOG_EQUATION_EXP        1
#define FOG_EQUATION_EXP2        2

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

    static void initRenderingPhase(glm::mat4 &mModelMatrix, glm::mat4 &mView);

    static void renderGround();

    static void renderTorus(glm::mat4);

    static void renderHouses(glm::mat4);

private fields:
    static GLFWwindow *wnd;
    static VertexBufferObject vboSceneObjects, vboCubeInd, vboCube, vboCylinder;
    static UINT uiVAOs[2];
    static Texture tTextures[NUMTEXTURES];
    static FlyingCamera cCamera;
    static Skybox mainSkybox;
    static CObjModel mdlHouse;
    static CObjModel treasure;
    static DirLight dlSun;
    static PointLight plLight;
    static SpotLight slFlashLight;
    static float fGlobalAngle;
    static float fTextureContribution;
    static bool isRotating;
    static Texture chessTexture;
    static bool isColorSelecting;
    static bool isLight;
    static CObjModel suzanne;
    static Mesh *mesh;
};


#endif //OPENGL2_APP_H
