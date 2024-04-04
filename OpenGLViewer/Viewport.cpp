#include "Viewport.h"


void HandleFramebufferSize(GLFWwindow* _window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int SViewport::Initialize(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, M_I_GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, M_I_GLFW_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(M_I_WIDTH, M_I_HEIGHT, M_S_TITLE, NULL, NULL);

	if (!m_pWindow)
	{
		std::cout << "ERROR: GLFW Window Creation failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow, HandleFramebufferSize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: GLAD Initialisation failed" << std::endl;
		return -2;
	}

	return 0;
}

int SViewport::Update(void)
{
	return 0;
}

int SViewport::Draw(void)
{
	glClearColor(M_F_RED, M_F_GREEN, M_F_BLUE, M_F_ALPHA);
	
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(m_pWindow);


	return 0;
}

void SViewport::Finalize(void)
{
	glfwTerminate();
}
