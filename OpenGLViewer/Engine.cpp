#include "Engine.h"
#include "Shader.h"
#include "SVertex.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"

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
	SShader shaderProgram = SShader("VertexLit.glsl", "FragmentLit.glsl");

    SCamera camera{};
    camera.Init();

    SLight light{};
    light.Init(&shaderProgram);

    SMaterial material{};
    material.Init(&shaderProgram);

    SMesh mesh{};
    mesh.Init(&shaderProgram, &material);


    while (!glfwWindowShouldClose(m_viewport.GetWindow()))
    {
        m_viewport.Update();
        mesh.Update();

        m_viewport.Draw();
        light.Draw();
        material.Draw();
        mesh.Draw(camera);

		m_viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void CEngine::Finalize(void)
{
    m_viewport.Finalize();
}
