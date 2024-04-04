#include "Engine.h"

int CEngine::Initialize(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    m_viewport.Initialize();

    return 0;
}

int CEngine::Run(void)
{
    while (!glfwWindowShouldClose(m_viewport.GetWindow()))
    {
        m_viewport.Update();
        m_viewport.Draw();

        glfwPollEvents();
    }

    return 0;
}

void CEngine::Finalize(void)
{
    m_viewport.Finalize();
}
