/*
	How to use this code:

	Call init_timer before starting rendering, i.e., before calling
	glutMainLoop. Then, make sure your display function is organized
	roughly as the example below.
*/

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <float.h>

#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include "load_mesh.cpp"
#include <iostream>

float  					gTotalTimeElapsed 	= 0;
int 					gTotalFrames		= 0;
GLuint 					gTimer;

void init_timer()
{
	glGenQueries(1, &gTimer);
}

void start_timing()
{
	glBeginQuery(GL_TIME_ELAPSED, gTimer);
}

float stop_timing()
{
	glEndQuery(GL_TIME_ELAPSED);

	GLint available = GL_FALSE;
	while (available == GL_FALSE)
		glGetQueryObjectiv(gTimer, GL_QUERY_RESULT_AVAILABLE, &available);

	GLint result;
	glGetQueryObjectiv(gTimer, GL_QUERY_RESULT, &result);

	float timeElapsed = result / (1000.0f * 1000.0f * 1000.0f);
	return timeElapsed;
}

const float* mat4ToFloatPtr(const glm::mat4& mat) {
    return &mat[0][0];
}
/*
	Your display function should look roughly like the following.
*/
void display(GLFWwindow* window, int mode)
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// TODO: Clear the screen and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 	start_timing();

 	// TODO: Draw the bunny.
  	if (mode == 1){ // Immediate Mode로 Rendering
		glBegin(GL_TRIANGLES);
		unsigned int k0, k1, k2;
		for (int i =0; i < gTriangles.size(); i++){
			k0 = gTriangles[i].indices[0];
			k1 = gTriangles[i].indices[1];
			k2 = gTriangles[i].indices[2];

			glNormal3f(gNormals[k0].x, gNormals[k0].y, gNormals[k0].z);
			glVertex3f(gPositions[k0].x, gPositions[k0].y, gPositions[k0].z);

			glNormal3f(gNormals[k1].x, gNormals[k1].y, gNormals[k1].z);
			glVertex3f(gPositions[k1].x, gPositions[k1].y, gPositions[k1].z);

			glNormal3f(gNormals[k2].x, gNormals[k2].y, gNormals[k2].z);
			glVertex3f(gPositions[k2].x, gPositions[k2].y, gPositions[k2].z);
		}
		glEnd();
	}
	else{ // Vertex Arrays로 렌더링 Rendering
		GLuint positionBuffer;
		GLuint normalBuffer;
		GLuint indexBuffer;

		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, gPositions.size() * sizeof(Vector3), gPositions.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, gNormals.size() * sizeof(Vector3), gNormals.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, gTriangles.size() * sizeof(Triangle), gTriangles.data(), GL_STATIC_DRAW);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glNormalPointer(GL_FLOAT, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glDrawElements(GL_TRIANGLES, gTriangles.size() * 3, GL_UNSIGNED_INT, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}

	float timeElapsed = stop_timing();
  	gTotalFrames++;
  	gTotalTimeElapsed += timeElapsed;
  	float fps = gTotalFrames / gTotalTimeElapsed;
  	char string[1024] = {0};
  	sprintf(string, "OpenGL Bunny: %0.2f FPS", fps);
	
	/* glut 함수이므로 주석처리  
	glutSetWindowTitle(string);

	glutPostRedisplay();
  	glutSwapBuffers(); */

	// glfw 함수로 변경
  	glfwSetWindowTitle(window, string);

  	glfwSwapBuffers(window);
	glfwPollEvents();
}
