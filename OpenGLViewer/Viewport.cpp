#include "Viewport.h"
#include "SVertex.h"


void HandleFramebufferSize(GLFWwindow* _window, int width, int height)
{
	//glViewport(0, 0, width, height);
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

	m_shaderProgram = SShader("Vertex.glsl", "Fragment.glsl");

	//unsigned int vertexShader{};
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);

	//unsigned int fragmentShader{};
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//shaderProgram = glCreateProgram();

	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	return 0;
}

int SViewport::Update(void)
{
	return 0;
}

int SViewport::Draw(void)
{
	glClearColor(M_F_RED, M_F_GREEN, M_F_BLUE, M_F_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT);

	SVertex vertices[] = {
	glm::vec3(-0.5f, -0.5f, 0.0f),
	glm::vec3(0.5f, -0.5f, 0.0f),
	glm::vec3(0.0f, 0.5f, 0.0f)
	};

	unsigned int VBO{}; //vertex buffer object
	glGenBuffers(1, &VBO); //generiere buffer id

	unsigned int VAO{}; //vertex array object
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //binde id mit einem typ buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//kopiere daten auf gpu von cpu //Hint: Static Draw is set only once and used may times
	
	m_shaderProgram.Use();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0); //Tells gpu how to interpret data
	//takes data from memory managed by vbo (can have multiple vbo) bound to array:buffer)
	glEnableVertexAttribArray(0); //0 steht für location 0 im vertex shader;

	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 4);

	glDeleteBuffers(0, &VBO);

	glfwSwapBuffers(m_pWindow);

	return 0;
}

void SViewport::Finalize(void)
{
	glfwTerminate();
}
