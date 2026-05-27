#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

int gWindow = 0;


void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);

    glLineWidth(1.0f);

    const float radius = 0.5f;
    const float heightPerRotation = 1.0f / 3.0f;
    const int numPoints = 120;

    for (int i = 0; i < numPoints; i++) {
        float t = (float)i / (numPoints - 1) * 3.0f;
        float angle = 2.0f * 3.14159265f * t;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        float z = -1.0f + t * heightPerRotation;

        float r = (float)rand() / RAND_MAX;
        float g = (float)rand() / RAND_MAX;
        float b = (float)rand() / RAND_MAX;
        glColor3f(r, g, b);

        float squareSize = 0.04f;
        glBegin(GL_LINE_STRIP);
        glVertex3f(x - squareSize, y - squareSize, z);
        glVertex3f(x + squareSize, y - squareSize, z);
        glVertex3f(x + squareSize, y + squareSize, z);
        glVertex3f(x - squareSize, y + squareSize, z);
        glVertex3f(x - squareSize, y - squareSize, z);
        glEnd();
    }

    glPopMatrix();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("week12_test_01");
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}
