#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cmath>

// Minimal single-window example that draws filled polygon(s) using GL_TRIANGLES.

int gWindow = 0;
void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Use smooth shading to interpolate vertex colors across primitives.
    glShadeModel(GL_SMOOTH);
}

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Filled triangle using GL_TRIANGLES. Winding set to counter-clockwise as front face.
    glFrontFace(GL_CCW);

    // Use per-vertex colors so GL_SMOOTH interpolates between them across the triangle.
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); // red
        glVertex3f(0.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f); // green
        glVertex3f(50.0f, 50.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f); // blue
        glVertex3f(50.0f, 0.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

// ChangeSize: Reshape callback - sets an orthographic projection clipped to -100..100
void ChangeSize(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("week13_01");
    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}