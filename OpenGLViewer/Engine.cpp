#include "Engine.h"
#include "Shader.h"
#include "SVertex.h"
#include "Mesh.h"
#include "Material.h"
#include "Light.h"
#include "Camera.h"
#include "Input.h"
#include "Time.h"
#include "Meshdata.h"

int CEngine::Initialize(void)
{
    if (!glfwInit())
        return -1;

    m_viewport.Initialize();
    glfwSetInputMode(m_viewport.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SInput::Init(m_viewport.GetWindow());
    STime::Init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    int texUnits{};
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texUnits);
    std::cout << texUnits << std::endl;

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
    mesh.Init(&shaderProgram, &material, cubeverts, cubeindices);

    SMaterial material2{};
    material2.Init(&shaderProgram);

    SMesh mesh2{};
    mesh2.Init(&shaderProgram, &material, quadverts, quadindices);

    mesh2.Translate(0.0f, 1.0f, -3.0f);


    while (!glfwWindowShouldClose(m_viewport.GetWindow()))
    {
        STime::Update();

        m_viewport.Update();
        camera.Update();
        mesh.Update();
        mesh2.Update();

        m_viewport.Draw();
        light.Draw();

        material.Draw();
        mesh.Draw(camera);

        material2.Draw();
        mesh2.Draw(camera);

		m_viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void CEngine::Finalize(void)
{
    m_viewport.Finalize();
}
