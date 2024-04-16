#include "Engine.h"
#include "Shader.h"
#include "SVertex.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"
#include "Input.h"
#include "Time.h"

int CEngine::Initialize(void)
{
    if (!glfwInit())
        return -1;

    m_viewport.Initialize();
    glfwSetInputMode(m_viewport.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SInput::Init(m_viewport.GetWindow());
    STime::Init();
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

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
        STime::Update();

        m_viewport.Update();
        camera.Update();
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
