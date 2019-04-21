

#include <iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>


using namespace std;

const GLfloat vertices[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   1.0f, 1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,
	   1.0f, 1.0f, 0.0f,
	   -1.0f, 1.0f, 0.0f
};

const GLfloat colors[] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};

const GLchar* vertex120 = R"END(

#version 120

uniform mat4 matrix;
attribute vec4 inColor;
attribute vec4 inPosition;

varying vec4 outColor;

void main()
{
    outColor = inColor;
    gl_Position = inPosition * matrix;
}
)END";

const GLchar* raster120 = R"END(
#version 120
varying vec4 outColor;
void main()
{
    gl_FragColor = outColor;
}
)END";

int main()
{
	GLFWwindow *window;

	if (!glfwInit())
	{
		GLenum error = glGetError();
		cout << error;
		exit(EXIT_FAILURE);
	}


	window = glfwCreateWindow(800, 800, "First Shader", 0, 0);

	if (!window)
	{
		cout << "Window creation error";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_FALSE;
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		cout << "OpenGL Error: " << error;
	}

	GLenum glewinit = glewInit();
	if (glewinit != GLEW_OK) {
		std::cout << "Glew not okay! " << glewinit;
		exit(EXIT_FAILURE);
	}

	//vertex shader

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex120, 0);
	glCompileShader(vertexShader);

	GLint compilationStatus;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE)
	{
		GLchar message[256];
		glGetShaderInfoLog(vertexShader, sizeof(message), 0, &message[0]);
		cout << message;
		exit(1);
	}


	//fragment shader

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &raster120, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE)
	{
		GLchar message[256];
		glGetShaderInfoLog(fragmentShader, sizeof(message), 0, &message[0]);
		cout << message;
		exit(1);
	}

	//Create program

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compilationStatus);

	if (compilationStatus == GL_FALSE)
	{
		GLchar message[256];
		glGetShaderInfoLog(shaderProgram, sizeof(message), 0, &message[0]);
		cout << message;
		exit(1);
	}

	glUseProgram(shaderProgram);

	//Vertex and Color buffer set up (VOB)

	GLuint vertexBuffer;
	GLuint colorBuffer;
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &colorBuffer);

	//send data to GPU

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint attribPosition = glGetAttribLocation(shaderProgram, "inPosition");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint attribColor = glGetAttribLocation(shaderProgram, "inColor");
	glEnableVertexAttribArray(attribColor);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//uniforms

	GLuint attribMatrix = glGetUniformLocation(shaderProgram, "matrix");

	float alpha = 0.0f;
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float sa = 0.5 * sin(alpha);
		float ca = -0.5 * cos(alpha);
		alpha += 0.001f;

		const GLfloat matrix[] = {
			sa, -ca, 0, 0,
			ca, sa, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		glUniformMatrix4fv(attribMatrix, 1, GL_FALSE, matrix);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

