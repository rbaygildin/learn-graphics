#include "../common.h"
#include "flyingCamera.h"
#include <glm/gtx/rotate_vector.hpp>

const float PI = float(atan(1.0) * 4.0);

FlyingCamera::FlyingCamera(GLFWwindow *wnd, int w, int h) {
    vEye = glm::vec3(0.0f, 0.0f, 0.0f);
    vView = glm::vec3(0.0f, 0.0, -1.0f);
    vUp = glm::vec3(0.0f, 1.0f, 0.0f);
    fSpeed = 25.0f;
    fSensitivity = 0.0001f;
    this->wnd = wnd;
    this->w = w;
    this->h = h;
}

FlyingCamera::FlyingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed,
                           float a_fSensitivity, GLFWwindow *wnd, int w, int h) {
    vEye = a_vEye;
    vView = a_vView;
    vUp = a_vUp;
    fSpeed = a_fSpeed;
    fSensitivity = 0.0001f;
    this->wnd = wnd;
    this->w = w;
    this->h = h;
}

// Checks for moving of mouse and rotates camera.
void FlyingCamera::RotateWithMouse(double xPos, double yPos) {
    int iCentX = w >> 1, iCentY = h >> 1;

    float deltaX = (float) (iCentX - xPos) * fSensitivity;
    float deltaY = (float) (iCentY - yPos) * fSensitivity;

    if (deltaX != 0.0f) {
        vView -= vEye;
        vView = glm::rotate(vView, deltaX, glm::vec3(0.0f, 1.0f, 0.0f));
        vView += vEye;
    }
    if (deltaY != 0.0f) {
        glm::vec3 vAxis = glm::cross(vView - vEye, vUp);
        vAxis = glm::normalize(vAxis);
        float fAngle = deltaY;
        float fNewAngle = fAngle + GetAngleX();
        if (fNewAngle > -90.00f && fNewAngle < 90.00f) {
            vView -= vEye;
            vView = glm::rotate(vView, deltaY, vAxis);
            vView += vEye;
        }
    }
}

// Gets Y angle of camera (head turning left and right).
float FlyingCamera::GetAngleY() {
    glm::vec3 vDir = vView - vEye;
    vDir.y = 0.0f;
    glm::normalize(vDir);
    float fAngle = acos(glm::dot(glm::vec3(0, 0, -1), vDir)) * (180.0f / PI);
    if (vDir.x < 0)
        fAngle = 360.0f - fAngle;
    return fAngle;
}

// Gets X angle of camera (head turning up and down).
float FlyingCamera::GetAngleX() {
    glm::vec3 vDir = vView - vEye;
    vDir = glm::normalize(vDir);
    glm::vec3 vDir2 = vDir;
    vDir2.y = 0.0f;
    vDir2 = glm::normalize(vDir2);
    float fAngle = acos(glm::dot(vDir2, vDir)) * (180.0f / PI);
    if (vDir.y < 0)
        fAngle *= -1.0f;
    return fAngle;
}

// Sets Keys for moving camera.
// a_iForw - move forward Key
// a_iBack - move backward Key
// a_iLeft - strafe left Key
// a_iRight - strafe right Key
void FlyingCamera::SetMovingKeys(int a_iForw, int a_iBack, int a_iLeft, int a_iRight) {
    iForw = a_iForw;
    iBack = a_iBack;
    iLeft = a_iLeft;
    iRight = a_iRight;
}

// Performs updates of camera - moving and rotating.
void FlyingCamera::Update(int key) {
//    RotateWithMouse(0, 0);

    // Get view direction
    glm::vec3 vMove = vView - vEye;
    vMove = glm::normalize(vMove);
    vMove *= fSpeed;

    glm::vec3 vStrafe = glm::cross(vView - vEye, vUp);
    vStrafe = glm::normalize(vStrafe);
    vStrafe *= fSpeed;

    int iMove = 0;
    glm::vec3 vMoveBy;
    // Get vector of move
    if (key == GLFW_KEY_UP)
        vMoveBy += vMove * 0.1f;
    if (key == GLFW_KEY_DOWN)
        vMoveBy -= vMove * 0.1f;
    if (key == GLFW_KEY_LEFT)
        vMoveBy -= vStrafe * 0.1f;
    if (key == GLFW_KEY_RIGHT)
        vMoveBy += vStrafe * 0.1f;
    vEye += vMoveBy;
    vView += vMoveBy;
}

// Sets mouse cursor back to the center of window.
void FlyingCamera::ResetMouse() {
    int left, right, bottom, top;
    double xPos, yPos;
    glfwGetWindowFrameSize(wnd, &left, &top, &right, &bottom);
    glfwGetCursorPos(wnd, &xPos, &yPos);
    int iCentX = (left + right) >> 1, iCentY = (top + bottom) >> 1;
}

// Returns proper modelview matrix to make camera look.
glm::mat4 FlyingCamera::Look() {
    return glm::lookAt(vEye, vView, vUp);
}

void FlyingCamera::SetWindowSize(int w, int h) {
    this->w = w;
    this->h = h;
}
