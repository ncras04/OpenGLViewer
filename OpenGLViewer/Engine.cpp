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
#include "Skybox.h"

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

    SShader potProgram = SShader("VertPot.glsl", "FragPot.glsl");


    SCamera camera{};
    camera.Init();

    SLight light{};
    light.Init(&shaderProgram);

    SLight light2{};
    light2.Init(&potProgram);

    SMaterial material{};
    material.Init(&shaderProgram);

    SMesh mesh{};
    mesh.Init(&shaderProgram, &material, cubeverts, cubeindices);

    SMaterial material2{};
    material2.Init(&potProgram);

    SMesh mesh2{};
    mesh2.Init(&potProgram, &material, potverts, potindices);

    mesh2.Translate(0.0f, -3.0f, -5.0f);

    SSkybox sbox{};
    sbox.Init();


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
        //mesh.Draw(camera);

        light2.Draw();
        material2.Draw();
        mesh2.Draw(camera);

        sbox.Draw(camera);

		m_viewport.LateDraw();

        glfwPollEvents();
    }

    return 0;
}

void CEngine::Finalize(void)
{
    m_viewport.Finalize();
}
