// OpenGL02.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include<GLFW/glfw3.h>
#include<math.h>

using namespace std;

const int steps = 50.0f;
const float angle = 3.1415926f * 2.0f / steps;

int main()
{
	GLFWwindow *window;

	if (!glfwInit())
	{
		cout << "error intiating opengl";
		return -1;
	}

	window = glfwCreateWindow(800, 800, "Circle", 0, 0);

	if (!window)
	{
		cout << "error rreating window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	float xpos = 0.0f;
	float ypos = 0.0f;
	float radius = 1.0f;

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		float prevX = xpos;
		float prevY = ypos - radius;

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);

		for (int i = 0; i <= steps; i++)
		{
			float newXpos = radius * sin(angle * i);
			float newYpos = -radius * cos(angle * i);

			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(prevX, prevY, 0.0f);
			glVertex3f(newXpos, newYpos, 0.0f);

			prevX = newXpos;
			prevY = newYpos;
		}

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
