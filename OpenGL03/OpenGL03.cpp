// OpenGL03.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include<GLFW/glfw3.h>

using namespace std;

void DrawCircle(float r, float g, float b)
{
	const int steps = 150.0f;
	float radius = 1.0f;
	const float angle = 13.1415926 * 2 / steps;

	float prevX = 0.0f;
	float prevY = 0.0f;

	for (int i = 0; i <= steps; i++)
	{
		float newX = radius * sin(angle * i);
		float newY = -radius * cos(angle * i);

		glColor3f(r, g, b);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(prevX, prevY, 0.0f);
		glVertex3f(newX, newY, 0.0f);
		glEnd();

		prevX = newX;
		prevY = newY;
	}
}



int main()
{
	if (!glfwInit())
	{
		cout << "error initiating opengl";
		return -1;
	}

	GLFWwindow *window;

	window = glfwCreateWindow(800, 800, "Relative transformation", 0, 0);

	if (!window)
	{
		cout << "error creating window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.1f, 0.1f, 1.0f);

	float angleEarth = 0.0f;
	float angleMoon = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		angleEarth += 0.1f;
		angleMoon += 0.2f;
		glClearColor(1.0f, 1.0, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawCircle(0.0f, 1.0, 1.0f);
		{
			glPushMatrix();
			glRotatef(angleEarth, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f, 5.0f, 0.0f);
			glScalef(0.6f, 0.6f, 1.0f);
			DrawCircle(1.0f, 0.0f, 1.0f);
			{
				glPushMatrix();
				glRotatef(angleMoon ,0.0f, 0.0f, 1.0f);
				glTranslatef(0.0f, 3.0f, 0.0f);
				glScalef(0.5f, 0.5f, 1);
				DrawCircle(1.0f, 1.0f, 0.0f);
				glPopMatrix();
			}
			glPopMatrix();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

