//
// Created by Max Heartfield on 06.12.17.
//

#include "app.h"
#include <boost/compute/command_queue.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/interop/opengl.hpp>
#include <boost/compute/utility/dim.hpp>
#include <boost/compute/utility/source.hpp>
#include <iostream>

using namespace std;

namespace compute = boost::compute;

const char source[] = BOOST_COMPUTE_STRINGIZE_SOURCE(
// map value to color
        float4 color(uint i)
        {
            uchar c = i;
            uchar x = 35;
            uchar y = 25;
            uchar z = 15;
            uchar max = 255;

            if(i == 256)
                return (float4)(0, 0, 0, 255);
            else
                return (float4)(max-x*i, max-y*i, max-z*i, max) / 255.f;
        }

        __kernel void mandelbrot(__write_only image2d_t image)
        {
            const uint x_coord = get_global_id(0);
            const uint y_coord = get_global_id(1);
            const uint width = get_global_size(0);
            const uint height = get_global_size(1);

            float x_origin = ((float) x_coord / width) * 3.25f - 2.0f;
            float y_origin = ((float) y_coord / height) * 2.5f - 1.25f;

            float x = 0.0f;
            float y = 0.0f;

            uint i = 0;
            while(x*x + y*y <= 4.f && i < 256){
                float tmp = x*x - y*y + x_origin;
                y = 2*x*y + y_origin;
                x = tmp;
                i++;
            }

            int2 coord = { x_coord, y_coord };
            write_imagef(image, coord, color(i));
        };
);


compute::context context_;
compute::command_queue queue_;
compute::program program_;
GLuint gl_texture_;
compute::opengl_texture cl_texture_;


void initCLProgram(){
    context_ = compute::opengl_create_shared_context();

    // get gpu device
    compute::device gpu = context_.get_device();
    std::cout << "device: " << gpu.name() << std::endl;

    // setup command queue
    queue_ = compute::command_queue(context_, gpu);

    // build mandelbrot program
    program_ = compute::program::create_with_source(source, context_);
    program_.build();
}

void repaintMandlebrot(){
    // generate new texture
    glGenTextures(1, &gl_texture_);
    glBindTexture(GL_TEXTURE_2D, gl_texture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, 255, 255, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0
    );

    // create opencl object for the texture
    cl_texture_ = compute::opengl_texture(
            context_, GL_TEXTURE_2D, 0, gl_texture_, CL_MEM_WRITE_ONLY
    );

    compute::kernel kernel(program_, "mandelbrot");
    kernel.set_arg(0, cl_texture_);

    // acquire the opengl texture so it can be used in opencl
    compute::opengl_enqueue_acquire_gl_objects(1, &cl_texture_.get(), queue_);

    // execute the mandelbrot kernel
    queue_.enqueue_nd_range_kernel(
            kernel, compute::dim(0, 0), compute::dim(255, 255), compute::dim(1, 1)
    );

    // release the opengl texture so it can be used by opengl
    compute::opengl_enqueue_release_gl_objects(1, &cl_texture_.get(), queue_);

    // ensure opencl is finished before rendering in opengl
    queue_.finish();

    // draw a single quad with the mandelbrot image texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gl_texture_);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}


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
PointLight App::plLight;
SpotLight App::slFlashLight;
CObjModel App::treasure, App::suzanne;


float App::fGlobalAngle;
float App::fTextureContribution = 0.5f;
bool App::isRotating = false;
bool App::isColorSelecting = false;
bool App::isLight = false;

bool isFog = false;
bool isColorMaterial = false;
bool isFogMode = true;

Texture App::chessTexture;

#define GREY_FOG 0.6f, 0.6f, 0.6f, 1.0f
#define RED_FOG 0.8f, 0.1f, 0.1f, 1.0f
#define BLUE_FOG 0.1f, 0.1f, 0.8f, 1.0f
#define GREEN_FOG 0.1f, 0.2f, 0.1f, 1.0f
#define YELLOW_FOG 0.1f, 0.8f, 0.8f, 1.0f

namespace FogParameters {
    float fDensity = 0.06f;
    float fStart = 10.0f;
    float fEnd = 75.0f;
    glm::vec4 vFogColor = glm::vec4(GREY_FOG);
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
    initCLProgram();
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
        glm::mat4 mModelMatrix, mView;
        initRenderingPhase(mModelMatrix, mView);
        renderGround();
//        repaintMandlebrot();

        renderTorus(mModelMatrix);
        fGlobalAngle = static_cast<float>(glfwGetTime() * 10.0f);
        renderHouses(mModelMatrix);

        glfwSwapBuffers(wnd);
        glfwPollEvents();
    }

}

void App::initRenderingPhase(glm::mat4 &mModelMatrix, glm::mat4 &mView) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    program.SetUniform("isColorMaterial", (int) isColorMaterial);
    program.SetUniform("materialColor", glm::vec4(1.0, 0.0, 0.0, 1.0));

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

    sun.ambient = 0.5f;
    sun.color = glm::vec3(1.0f, 1.0f, 1.0f);
    sun.SetUniformData(&program, "sunLight");

//    mainSkybox.RenderSkybox();

    glm::mat4 mModelToCamera;

    glBindVertexArray(uiVAOs[0]);

    dlSun.SetUniformData(&program, "sunLight");
    plLight.SetUniformData(&program, "pointLight");
    slFlashLight.SetUniformData(&program, "spotLight");

    program.SetUniform("vColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    program.SetUniform("matrices.modelMatrix", glm::mat4(1.0f));
    program.SetUniform("matrices.normalMatrix", glm::mat4(1.0f));
}

void App::renderTorus(glm::mat4 mModelMatrix) {
    // render torus
    tTextures[1].BindTexture();

    float R = 20;
    float tX = 100;
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
}

void App::renderGround() {
    // Render ground
    tTextures[0].BindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void App::renderHouses(glm::mat4 mModelMatrix) {
    FOR(i, 3) {
        FOR(j, 3) {
            glm::vec3 vPos = glm::vec3(50 + j * -100.0f, 0.0, 50 + i * -100.0f);
            mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
            mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 8.0, 8.0f));
            program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
            program.SetUniform("matrices.modelMatrix", &mModelMatrix);
            mdlHouse.RenderModel();
        }
    }

//    FOR(i, 2) {
//        glm::vec3 vPos = glm::vec3(20.0f, 0.0, 80 + i * -100.0f);
//        mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
//        mModelMatrix = glm::scale(mModelMatrix, glm::vec3(8.0f, 9.0, 8.0f));
//        program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
//        program.SetUniform("matrices.modelMatrix", &mModelMatrix);
//        mainSkybox.RenderSkybox();
//    }


//    program.SetUniform("isMaterialColor", 1);
//    program.SetUniform("materialColor", glm::vec4(RED_FOG));
    auto a = static_cast<float>(fmod(glfwGetTime(), 100));
    FOR(i, 3) {
        FOR(j, 3) {
            glm::vec3 vPos = glm::vec3(200 + j * -100.0f, 20, 50 + i * -100.0f);
            mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
            mModelMatrix = glm::scale(mModelMatrix, glm::vec3(4.0f, 4.0, 4.0f));
            mModelMatrix = glm::rotate(mModelMatrix, a, glm::vec3(0.0f, 1.0f, 0.0f));
            program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
            program.SetUniform("matrices.modelMatrix", &mModelMatrix);
            suzanne.RenderModel();
        }
    }

    FOR(i, 3) {
        FOR(j, 3) {
            glm::vec3 vPos = glm::vec3(200 + j * -100.0f, 50, 50 + i * -100.0f);
            mModelMatrix = glm::translate(glm::mat4(1.0), vPos);
            mModelMatrix = glm::scale(mModelMatrix, glm::vec3(4.0f, 4.0, 4.0f));
            mModelMatrix = glm::rotate(mModelMatrix, a, glm::vec3(0.0f, 1.0f, 0.0f));
            program.SetUniform("matrices.normalMatrix", glm::transpose(glm::inverse(mModelMatrix)));
            program.SetUniform("matrices.modelMatrix", &mModelMatrix);
            treasure.RenderModel();
        }
    }
//    program.SetUniform("isMaterialColor", 0);
}


/**
 * Destroy objects
 */
void App::destroy() {
    Logger::info("Destroying scene");
    Logger::info("Delete textures");
    chessTexture.DeleteTexture();
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
    chessTexture.LoadTexture2D("data/models/treasure/treasure_chest.JPG", true);
    chessTexture.SetFiltering(TEXTURE_FILTER_MAG_BILINEAR, TEXTURE_FILTER_MIN_NEAREST_MIPMAP);

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

    dlSun = DirLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(10 + sqrt(2.0f) / 2, 10 + -sqrt(2.0f) / 2, 10), 1.0f);
    slFlashLight = SpotLight(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(10.0f, 10.0f, 1.0f), 1,
                             15.0f, 0.6f);
    plLight = PointLight(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.6f, 0.1f, 0.007f, 0.0008f);
    mdlHouse.LoadModel("data/models/house/house.obj", "data/models/house/house.mtl");
    treasure.LoadModel("data/models/house/house2.obj", "data/models/house/house2.mtl");
    suzanne.LoadModel("data/models/suzanne/suzanne.obj", "data/models/suzanne/suzanne.mtl");
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
    if (key == GLFW_KEY_C) {
        if (!isColorSelecting) {
            BOOST_LOG_TRIVIAL(info) << "Select fog color";
            isColorSelecting = true;
            return;
        }
    }
    if (!isFogMode && key == GLFW_KEY_F) {
        isFogMode = true;
        return;
    }
    if (isFogMode && key == GLFW_KEY_E) {
        isColorSelecting = false;
        isFogMode = false;
        isLight = false;
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_E) {
        BOOST_LOG_TRIVIAL(info) << "Select fog color ends";
        isColorSelecting = false;
        isFogMode = false;
        isLight = false;
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_G) {
        BOOST_LOG_TRIVIAL(info) << "Grey fog chosen";
        if (isFogMode)
            FogParameters::vFogColor = glm::vec4(GREY_FOG);
        else
            plLight.vColor = glm::vec4(GREY_FOG);
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_R) {
        BOOST_LOG_TRIVIAL(info) << "Grey fog chosen";
        if (isFogMode)
            FogParameters::vFogColor = glm::vec4(RED_FOG);
        else
            plLight.vColor = glm::vec4(RED_FOG);
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_B) {
        BOOST_LOG_TRIVIAL(info) << "Grey fog chosen";
        if (isFogMode)
            FogParameters::vFogColor = glm::vec4(BLUE_FOG);
        else
            plLight.vColor = glm::vec4(BLUE_FOG);
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_G) {
        BOOST_LOG_TRIVIAL(info) << "Grey fog chosen";
        if (isFogMode)
            FogParameters::vFogColor = glm::vec4(GREEN_FOG);
        else
            plLight.vColor = glm::vec4(GREEN_FOG);
        return;
    }
    if (isColorSelecting && key == GLFW_KEY_Y) {
        BOOST_LOG_TRIVIAL(info) << "Grey fog chosen";
        if (isFogMode)
            FogParameters::vFogColor = glm::vec4(YELLOW_FOG);
        else
            plLight.vColor = glm::vec4(YELLOW_FOG);
        return;
    }
    if (key == GLFW_KEY_S)
        FogParameters::iFogEquation = FOG_EQUATION_EXP2;
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
    if(isLight && key == GLFW_KEY_U){
        plLight.vPosition = glm::vec3(plLight.vPosition.x, plLight.vPosition.y + 10, plLight.vPosition.z);
        return;
    }
    if(isLight && key == GLFW_KEY_D){
        plLight.vPosition = glm::vec3(plLight.vPosition.x, plLight.vPosition.y - 10, plLight.vPosition.z);
        return;
    }
    if(isLight && key == GLFW_KEY_EQUAL){
        plLight.vPosition = glm::vec3(plLight.vPosition.x + 10, plLight.vPosition.y, plLight.vPosition.z);
        return;
    }
    if(isLight && key == GLFW_KEY_MINUS){
        plLight.vPosition = glm::vec3(plLight.vPosition.x - 10, plLight.vPosition.y, plLight.vPosition.z);
        return;
    }
    if(isLight && key == GLFW_KEY_F){
        plLight.vPosition = glm::vec3(plLight.vPosition.x, plLight.vPosition.y, plLight.vPosition.z + 10);
        return;
    }
    if(isLight && key == GLFW_KEY_B){
        plLight.vPosition = glm::vec3(plLight.vPosition.x, plLight.vPosition.y, plLight.vPosition.z - 10);
        return;
    }
    if (key == GLFW_KEY_U) {
        if (FogParameters::iFogEquation == FOG_EQUATION_EXP || FogParameters::iFogEquation == FOG_EQUATION_EXP2) {
            BOOST_LOG_TRIVIAL(info) << "Increase density of fog";
            FogParameters::fDensity += 0.001;
        } else if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR) {
            if (FogParameters::fStart + 2.0 < FogParameters::fEnd) {
                FogParameters::fStart += 2.0;
                BOOST_LOG_TRIVIAL(info) << "Change start of fog [start =" << FogParameters::fStart << "]";
            }
        }
    }
    if (key == GLFW_KEY_D) {
        if (FogParameters::iFogEquation == FOG_EQUATION_EXP || FogParameters::iFogEquation == FOG_EQUATION_EXP2) {
            BOOST_LOG_TRIVIAL(info) << "Decrease density of fog";
            FogParameters::fDensity -= 0.001;
        } else if (FogParameters::iFogEquation == FOG_EQUATION_LINEAR) {
            if (FogParameters::fStart - 2.0 >= 3.0) {
                FogParameters::fStart -= 2.0;
                BOOST_LOG_TRIVIAL(info) << "Change start of fog [start =" << FogParameters::fStart << "]";
            }
        }
    }
    if(key == GLFW_KEY_W){
        isLight = true;
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

