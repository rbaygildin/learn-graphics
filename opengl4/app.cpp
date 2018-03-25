//
// Created by Max Heartfield on 06.12.17.
//

#include "app.h"

#define WINDOW_W 640
#define WINDOW_H 480

#define NUMTEXTURES 5
#define FOG_EQUATION_LINEAR        0
#define FOG_EQUATION_EXP        1
#define FOG_EQUATION_EXP2        2

GLFWwindow *App::wnd;
VertexBufferObject App::vboSceneObjects, App::vboCubeInd, App::vboCube, App::vboCylinder;
UINT App::uiVAOs[2];
Texture App::tTextures[NUMTEXTURES];
FlyingCamera App::cCamera(nullptr, 0, 0);
Skybox App::mainSkybox;
CObjModel App::mdlHouse;
DirLight App::dlSun;
float App::fGlobalAngle;
float App::fTextureContribution = 0.5f;
bool App::isRotating = false;

bool isFog = false;

namespace FogParameters {
    float fDensity = 0.06f;
    float fStart = 10.0f;
    float fEnd = 75.0f;
    glm::vec4 vFogColor = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
    int iFogEquation = FOG_EQUATION_LINEAR; // 0 = linear, 1 = exp, 2 = exp2
};

/**
 * Start and init context
 * @param argc
 * @param argv
 */
void App::start(int argc, char **argv) {
    if (!glfwInit()) {
        Logger::error("Could not to initialize GLFW context");
        exit(EXIT_FAILURE);
    }
    Logger::info("GLFW context loaded successfully");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    wnd = glfwCreateWindow(WINDOW_W, WINDOW_H, "OpenGL start", nullptr, nullptr);
    if (!wnd) {
        Logger::error("Window could not created");
        glfwDestroyWindow(wnd);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    Logger::info("Window created successfully");
    glfwMakeContextCurrent(wnd);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GL_FALSE)
        exit(EXIT_FAILURE);
    initScene();
    glfwSetKeyCallback(wnd, keyCallback);
    glfwSetCursorPosCallback(wnd, posCallback);
    glfwSetMouseButtonCallback(wnd, mouseCallback);
    glfwSetWindowSizeCallback(wnd, resizeCallback);
    glEnable(GL_DEPTH_TEST);
}

/**
 * Render objects
 */
void App::render() {
    Logger::info("Render content");

    program.UseProgram();


    while (!glfwWindowShouldClose(wnd)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 mModelMatrix, mView;
        glm::vec3 vCameraDir = glm::normalize(cCamera.vView - cCamera.vEye);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(FogParameters::vFogColor.r,
                     FogParameters::vFogColor.g,
                     FogParameters::vFogColor.b,
                     FogParameters::vFogColor.a);
        int w, h;
        glfwGetWindowSize(wnd, &w, &h);

        program.UseProgram();
        program.SetUniform("isFog", (int) isFog);

        program.SetUniform("matrices.projMatrix", glm::perspective(45.0f, w / (float) h, 0.5f, 1000.0f));
        program.SetUniform("gSampler", 0);
        program.SetUniform("fogParams.iEquation", FogParameters::iFogEquation);
        program.SetUniform("fogParams.vFogColor", FogParameters::vFogColor);
        mView = cCamera.Look();
        program.SetUniform("matrices.viewMatrix", &mView);

        mModelMatrix = glm::translate(glm::mat4(1.0f), cCamera.vEye);

        program.SetUniform("matrices.modelMatrix", &mModelMatrix);
        program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mView * mModelMatrix)));

        if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR) {
            program.SetUniform("fogParams.fStart", FogParameters::fStart);
            program.SetUniform("fogParams.fEnd", FogParameters::fEnd);
        } else
            program.SetUniform("fogParams.fDensity", FogParameters::fDensity);

        DirLight sun = dlSun;

        // We set full ambient for skybox, so that its color isn't affected by directional light

        sun.ambient = 0.2f;
        sun.color = glm::vec3(1.0f, 1.0f, 1.0f);
        sun.SetUniformData(&program, "sunLight");

//        mainSkybox.RenderSkybox();

        glm::mat4 mModelToCamera;

        glBindVertexArray(uiVAOs[0]);

        dlSun.SetUniformData(&program, "sunLight");

        program.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        program.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
        program.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));


        // Render ground
        tTextures[0].BindTexture();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // render torus
        tTextures[1].BindTexture();

        float R = 50;
        float tX = 30;
        float tY = 10;
        float tZ = 10;
        float k1 = 0.1;
        float k2 = 0.3;
        float c = 5;

        auto a = static_cast<float>(fmod(glfwGetTime(), 100));

        glm::vec3 vPos = glm::vec3(R * cos(a) + R * k2 * cos(c * a) + tX, tY, R * sin(a) + R * k2 * sin(c * a) + tZ);

        mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
        mModelMatrix = glm::rotate(mModelMatrix, static_cast<float>(glfwGetTime() * 2.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
        program.SetUniform("matrices.modelMatrix", &mModelMatrix);
        glDrawArrays(GL_TRIANGLES, 6, iTorusFaces * 3);

        tTextures[2].BindTexture();
        vPos = glm::vec3(tX + 5, tY, tZ + 5);
        mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
        mModelMatrix = glm::rotate(mModelMatrix, static_cast<float>(glfwGetTime() * 5.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
        program.SetUniform("matrices.modelMatrix", &mModelMatrix);
        glDrawArrays(GL_TRIANGLES, 6 + iTorusFaces * 3, iTorusFaces2 * 3);

        fGlobalAngle = static_cast<float>(glfwGetTime() * 10.0f);

        FOR(i, 3) {
            glm::vec3 vPos = glm::vec3(0.0f, 0.0, 50 + i * -100.0f);
            mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
            mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 8.0, 8.0f));
            program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
            program.SetUniform("matrices.modelMatrix", &mModelMatrix);
            mdlHouse.RenderModel();
        }

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

}

/**
 * Destroy objects
 */
void App::destroy() {
    Logger::info("Destroying scene");
    Logger::info("Delete textures");
    FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();
    Logger::info("Delete skybox");
    mainSkybox.DeleteSkybox();
    Logger::info("Delete program");
    program.DeleteProgram();
    FOR(i, NUMSHADERS)shShaders[i].DeleteShader();
    Logger::info("Delete objects");
    glDeleteVertexArrays(2, uiVAOs);
    vboSceneObjects.DeleteVBO();
    vboCubeInd.DeleteVBO();
    vboCube.DeleteVBO();
}

/**
 * Init scene
 */
void App::initScene() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Prepare all scene objects

    vboSceneObjects.CreateVBO();
    glGenVertexArrays(2, uiVAOs); // Create one VAO
    glBindVertexArray(uiVAOs[0]);

    vboSceneObjects.BindVBO();

    AddSceneObjects(vboSceneObjects);

    vboSceneObjects.UploadDataToGPU(GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), nullptr);
    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2),
                          (void *) sizeof(glm::vec3));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2),
                          (void *) (sizeof(glm::vec3) + sizeof(glm::vec2)));

    glBindVertexArray(uiVAOs[1]);

    vboCube.CreateVBO();
    vboCube.BindVBO();
    AddCube(vboCube);
    vboCube.UploadDataToGPU(GL_STATIC_DRAW);

    vboCubeInd.CreateVBO();
    // Bind indices
    vboCubeInd.BindVBO(GL_ELEMENT_ARRAY_BUFFER);
    vboCubeInd.AddData(&iCubeindices, sizeof(iCubeindices));
    vboCubeInd.UploadDataToGPU(GL_STATIC_DRAW);
//
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
    if (!PrepareShaderPrograms()) {
        Logger::error("Could not prepare program");
        exit(EXIT_FAILURE);
    }
    string sTextureNames[] = {"met_wall01a.jpg", "light.jpg", "grass.png", "tower.jpg", "ground.jpg",
                              "metal.png", "lego.jpg"};

    FOR(i, NUMTEXTURES) {
        tTextures[i].LoadTexture2D("data/textures/" + sTextureNames[i], true);
        tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
    }

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    cCamera = FlyingCamera(glm::vec3(0.0f, 10.0f, 120.0f), glm::vec3(0.0f, 10.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                           25.0f, 0.001f, wnd, WINDOW_W, WINDOW_H);
    cCamera.SetMovingKeys('W', 'S', 'A', 'D');
    string skyBoxSet = "moonwaw";
    string picFormat = ".jpeg";
    mainSkybox.LoadSkybox("data/skyboxes/" + skyBoxSet + "/", skyBoxSet + "_ft" + picFormat,
                          skyBoxSet + "_bk" + picFormat, skyBoxSet + "_lf" + picFormat,
                          skyBoxSet + "_rt" + picFormat, skyBoxSet + "_up" + picFormat,
                          skyBoxSet + "_dn" + picFormat);

    dlSun = DirLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 1.0f);
//    slFlashLight = SpotLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 10.0f, 1.0f), 1,
//                             15.0f, 0.6f);
//    plLight = PointLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.8f, 0.3f, 0.007f, 0.00008f);
    mdlHouse.LoadModel("data/models/house/house.obj", "data/models/house/house.mtl");
}

/**
 * Key callback
 * @param window
 * @param key
 * @param scanCode
 * @param action
 * @param mods
 */
void App::keyCallback(GLFWwindow *window, int key, int scanCode, int action, int mods) {
    if (key == GLFW_KEY_E && FogParameters::iFogEquation == FOG_EQUATION_EXP)
        FogParameters::iFogEquation = FOG_EQUATION_EXP2;
    if (key == GLFW_KEY_E && FogParameters::iFogEquation == FOG_EQUATION_EXP2)
        FogParameters::iFogEquation = FOG_EQUATION_EXP;
    if (key == GLFW_KEY_E)
        FogParameters::iFogEquation = FOG_EQUATION_EXP;
    if (key == GLFW_KEY_L)
        FogParameters::iFogEquation = FOG_EQUATION_LINEAR;
    if (key == GLFW_KEY_0) {
        isFog = false;
    }
    if (key == GLFW_KEY_1) {
        isFog = true;
    }
    if (key == GLFW_KEY_U) {
        if (FogParameters::iFogEquation == FOG_EQUATION_EXP) {
            BOOST_LOG_TRIVIAL(info) << "Increase density of fog";
            FogParameters::fDensity += 0.01;
        } else if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR) {
            if (FogParameters::fStart + 2.0 < FogParameters::fEnd) {
                FogParameters::fStart += 2.0;
                BOOST_LOG_TRIVIAL(info) << "Change start of fog [start =" << FogParameters::fStart << "]";
            }
        }
    }
    if (key == GLFW_KEY_D) {
        if (FogParameters::iFogEquation == FOG_EQUATION_EXP) {
            BOOST_LOG_TRIVIAL(info) << "Decrease density of fog";
            FogParameters::fDensity -= 0.01;
        } else if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR) {
            if (FogParameters::fStart - 2.0 >= 3.0) {
                FogParameters::fStart -= 2.0;
                BOOST_LOG_TRIVIAL(info) << "Change start of fog [start =" << FogParameters::fStart << "]";
            }
        }
    }
    if (key == GLFW_KEY_R)
        cCamera.ResetMouse();
    cCamera.Update(key);
}

/**
 * Cursor callback
 * @param window
 * @param xPos
 * @param yPos
 */
void App::posCallback(GLFWwindow *window, double xPos, double yPos) {
    BOOST_LOG_TRIVIAL(info) << "Captured cursor at x = " << xPos << ", y = " << yPos;
    if (isRotating) {
        Logger::info("Rotating camera");
        cCamera.RotateWithMouse(xPos, yPos);
    }
}

/**
 * Mouse callback
 * @param window
 * @param button
 * @param action
 * @param mods
 */
void App::mouseCallback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS)
            isRotating = true;
        else if (action == GLFW_RELEASE)
            isRotating = false;
    }
}

/**
 * Resize callback
 * @param window
 * @param width
 * @param height
 */
void App::resizeCallback(GLFWwindow *window, int width, int height) {
    cCamera.SetWindowSize(width, height);
}