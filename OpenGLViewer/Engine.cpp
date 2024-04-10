#include "Engine.h"
#include "SVertex.h"
#include "Shader.h"
#include "Mesh.h"

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
	SShader shaderProgram = SShader("Vertex.glsl", "Fragment.glsl");
    SMesh mesh{};
    mesh.Init(&shaderProgram, nullptr);

    while (!glfwWindowShouldClose(m_viewport.GetWindow()))
    {
        m_viewport.Update();
        mesh.Update();
        m_viewport.Draw();

        mesh.Draw();
		m_viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void CEngine::Finalize(void)
{
    m_viewport.Finalize();
}
