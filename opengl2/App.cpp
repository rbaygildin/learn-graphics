//
// Created by Max Heartfield on 06.12.17.
//

#include "App.h"

GLFWwindow *App::wnd;
CVertexBufferObject App::vboSceneObjects, App::vboCubeInd, App::vboCube;
UINT App::uiVAOs[2];
CTexture App::tTextures[NUMTEXTURES];
CFlyingCamera App::cCamera(nullptr);
CSkybox App::sbMainSkybox;
CDirectionalLight App::dlSun;
float App::fGlobalAngle;
float App::fTextureContribution = 0.5f;

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
    wnd = glfwCreateWindow(640, 480, "OpenGL start", nullptr, nullptr);
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
    glfwSetCursorPosCallback(wnd, mouseCallback);
}

void App::render() {
    Logger::info("Render content");

    while (!glfwWindowShouldClose(wnd)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        spMain.UseProgram();

        glm::mat4 mModelMatrix, mView;

        glm::vec3 vCameraDir = glm::normalize(cCamera.vView-cCamera.vEye);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        spMain.UseProgram();

        int w, h;
        glfwGetWindowSize(wnd, &w, &h);

        spMain.SetUniform("matrices.projMatrix", glm::perspective(45.0f, w / (float) h, 0.5f, 1000.0f));
        spMain.SetUniform("gSamplers[0]", 0);
        spMain.SetUniform("gSamplers[1]", 1);
        spMain.SetUniform("fTextureContributions[0]", 1.0f);
        spMain.SetUniform("fTextureContributions[1]", fTextureContribution);
        spMain.SetUniform("numTextures", 1);

        mView = cCamera.Look();
        spMain.SetUniform("matrices.viewMatrix", &mView);

        mModelMatrix = glm::translate(glm::mat4(1.0f), cCamera.vEye);

        spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
        spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mView*mModelMatrix)));

        CDirectionalLight dlSun2 = dlSun;

        // We set full ambient for skybox, so that its color isn't affected by directional light

        dlSun2.fAmbient = 1.0f;
        dlSun2.vColor = glm::vec3(1.0f, 1.0f, 1.0f);
        dlSun2.SetUniformData(&spMain, "sunLight");

        sbMainSkybox.RenderSkybox();
        glBindVertexArray(uiVAOs[1]);
        // Render cubes
        glm::mat4 mModelToCamera;

        tTextures[3].BindTexture();
        tTextures[1].BindTexture(1);

        spMain.SetUniform("fTextureContributions[0]", 1.0f - fTextureContribution);
        spMain.SetUniform("numTextures", 2);

        float PI = float(atan(1.0)*4.0);

        glEnable(GL_CULL_FACE);
        //glFrontFace(GL_CCW); //Done by default
        glm::vec3 vPos2 = glm::vec3(30.0f, 8.0f, 0.0f);
        mModelMatrix = glm::mat4(1.0f);
        mModelMatrix = glm::translate(mModelMatrix, vPos2);
        mModelMatrix = glm::scale(mModelMatrix, glm::vec3(16.0f, 16.0f, 16.0f));
        // We need to transform normals properly, it's done by transpose of inverse matrix of rotations and scales
        spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
        spMain.SetUniform("matrices.modelMatrix", mModelMatrix);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
        glDisable(GL_CULL_FACE);

        spMain.SetUniform("fTextureContributions[0]", 1.0f);
        spMain.SetUniform("numTextures", 1);

        glBindVertexArray(uiVAOs[0]);

        dlSun.SetUniformData(&spMain, "sunLight");

        spMain.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        spMain.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
        spMain.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));


        // Render ground
        tTextures[0].BindTexture();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // render torus
        tTextures[1].BindTexture();
        // Now it's gonna float in the air
        glm::vec3 vPos = glm::vec3(0.0f, 10.0, 0.0f);
        mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
        mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
        spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
        glDrawArrays(GL_TRIANGLES, 6, iTorusFaces * 3);

        tTextures[2].BindTexture();
        mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
        mModelMatrix = glm::rotate(mModelMatrix, fGlobalAngle, glm::vec3(1.0f, 0.0f, 0.0f));
        spMain.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
        spMain.SetUniform("matrices.modelMatrix", &mModelMatrix);
        glDrawArrays(GL_TRIANGLES, 6 + iTorusFaces * 3, iTorusFaces2 * 3);

//        cCamera.Update();

        glEnable(GL_DEPTH_TEST);

//        if (Keys::Key('Q')) fTextureContribution += appMain.sof(-0.2f);
//        if (Keys::Key('E')) fTextureContribution += appMain.sof(0.2f);
//        fTextureContribution = min(max(0.0f, fTextureContribution), 1.0f);
//
//        if(Keys::Onekey(VK_ESCAPE))PostQuitMessage(0);
//        fGlobalAngle += appMain.sof(1.0f);
//        oglControl->SwapBuffers();

        glfwSwapBuffers(wnd);
        glfwPollEvents();

    }

}

void App::destroy() {
    FOR(i, NUMTEXTURES)tTextures[i].DeleteTexture();
    sbMainSkybox.DeleteSkybox();
    spMain.DeleteProgram();
    FOR(i, NUMSHADERS)shShaders[i].DeleteShader();

    glDeleteVertexArrays(2, uiVAOs);
    vboSceneObjects.DeleteVBO();
    vboCubeInd.DeleteVBO();
    vboCube.DeleteVBO();
}

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
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
//
    if (!PrepareShaderPrograms()) {
        Logger::error("Could not prepare program");
        exit(EXIT_FAILURE);
    }
//    // Load textures
//
    string sTextureNames[] = {"grass.png", "met_wall01a.jpg", "tower.jpg", "box.jpg", "ground.jpg"};

    FOR(i, NUMTEXTURES) {
        tTextures[i].LoadTexture2D("data/textures/" + sTextureNames[i], true);
        tTextures[i].SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_BILINEAR_MIPMAP);
    }

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
////    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
//
//    cCamera = CFlyingCamera(glm::vec3(0.0f, 10.0f, 120.0f), glm::vec3(0.0f, 10.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.0f),
//                            25.0f, 0.001f, wnd);
//    cCamera.SetMovingKeys('W', 'S', 'A', 'D');
//
    sbMainSkybox.LoadSkybox("data/skyboxes/jajlands1/", "jajlands1_ft.jpg", "jajlands1_bk.jpg", "jajlands1_lf.jpg",
                            "jajlands1_rt.jpg", "jajlands1_up.jpg", "jajlands1_dn.jpg");
//
//    dlSun = CDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(sqrt(2.0f) / 2, -sqrt(2.0f) / 2, 0), 1.0f);
}

void App::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
//    cCamera.Update();
}

void App::mouseCallback(GLFWwindow *window, double xPos, double yPos) {
    BOOST_LOG_TRIVIAL(info) << "Captured cursor at x = " << xPos << ", y = " << yPos;
//    cCamera.Update();
}
