

#include <iostream>
#include<GLFW/glfw3.h>

using namespace std;

int main()
{
	GLFWwindow *window;

	if (!glfwInit())
	{
		cout << "Error";
		return -1;
	}

	window = glfwCreateWindow(800, 800, "Hello Opengl", 0, 0);

	if (!window) 
	{
		cout << "Window creation error";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	//Loop
	while(!glfwWindowShouldClose(window)) 
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-0.6f, -0.4f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.6f, -0.4f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.6f, 0.0f);
		glEnd();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


