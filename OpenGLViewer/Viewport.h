#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "CShader.h"

struct SViewport
{
    inline SViewport(){}
    inline GLFWwindow* GetWindow(void) { return m_pWindow; }

    // Kann von IObject vererbt werden
    int Initialize(void);
    int Update(void);
    int Draw(void);
    void Finalize(void);

private:
    GLFWwindow* m_pWindow = nullptr;
	SShader m_shaderProgram;


	const int M_I_GLFW_VERSION_MAJOR = 3;
	const int M_I_GLFW_VERSION_MINOR = 3;
	const int M_I_WIDTH = 640;
	const int M_I_HEIGHT = 360;
	const char* M_S_TITLE = "OVL UE2";
	const int M_I_OFFSET_X = 0;
	const int M_I_OFFSET_Y = 0;
	const float M_F_RED = 0.0f;
	const float M_F_GREEN = 1.0f;
	const float M_F_BLUE = 0.0f;
	const float M_F_ALPHA = 1.0f;
};
#endif // !VIEWPORT_H
