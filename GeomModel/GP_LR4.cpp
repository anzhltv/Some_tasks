// GP_LR4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//#include<gl\glut.h>
/* void Draw()
{

}

void Initi()
{

}

int main(int argc, char** argv)
{

	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Lesson 1");
	//reg
	glurDisplayFunc(Draw);
	Initi();
	glutMainLoop();
	return 0;
} */
#include "glew.h"
#include "glfw3.h"
#include <glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}