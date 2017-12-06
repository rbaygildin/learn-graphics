#pragma once

class CFlyingCamera
{
public:
	glm::vec3 vEye, vView, vUp;
	float fSpeed;
	float fSensitivity; // How many degrees to rotate per pixel moved by mouse (nice value is 0.10)

	// Main functions
    void RotateWithMouse(double xPos, double yPos);
	void Update(int key);
	glm::mat4 Look();

	void SetMovingKeys(int a_iForw, int a_iBack, int a_iLeft, int a_iRight);
	void ResetMouse();

	// Functions that get viewing angles
	float GetAngleX(), GetAngleY();

	// Constructors
	explicit CFlyingCamera(GLFWwindow *wnd);
	CFlyingCamera(glm::vec3 a_vEye, glm::vec3 a_vView, glm::vec3 a_vUp, float a_fSpeed,
                      float a_fSensitivity, GLFWwindow *wnd);

private:
// For mosue rotation
	int iForw, iBack, iLeft, iRight;
	GLFWwindow *wnd;
};
