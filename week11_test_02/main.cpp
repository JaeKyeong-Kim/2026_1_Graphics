#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

int gWindowSpacing = 0;
int gWindowLength = 0;

void RenderSceneSpacing(void)
{
    std::cout << "RenderSceneSpacing" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat worldSize = 800.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, worldSize, 0.0, worldSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const int lineCount = 10;
    const GLfloat margin = 12.0f;

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE);

    for (int i = 0; i < lineCount; ++i)
    {
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin);
        GLint factor = 4 - static_cast<GLint>(3.0f * t + 0.5f);

        glLineStipple(factor, 0x00FF);
        glBegin(GL_LINES);
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glDisable(GL_LINE_STIPPLE);

    glutSwapBuffers();
}

void RenderSceneLength(void)
{
    std::cout << "RenderSceneLength" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat worldSize = 800.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, worldSize, 0.0, worldSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const int lineCount = 10;
    const GLfloat margin = 12.0f;

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE);

    for (int i = 0; i < lineCount; ++i)
    {
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin);
        GLint onBits = 12 - i;
        GLushort pattern = static_cast<GLushort>(((1u << onBits) - 1u) << (16 - onBits));

        glLineStipple(1, pattern);
        glBegin(GL_LINES);
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glDisable(GL_LINE_STIPPLE);

    glutSwapBuffers();
}

void ChangeSizeSpacing(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void ChangeSizeLength(GLsizei w, GLsizei h)
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
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    gWindowSpacing = glutCreateWindow("week11_test_02 - stipple spacing");
    SetupRC();
    glutDisplayFunc(RenderSceneSpacing);
    glutReshapeFunc(ChangeSizeSpacing);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(760, 100);
    gWindowLength = glutCreateWindow("week11_test_02 - stipple length");
    SetupRC();
    glutDisplayFunc(RenderSceneLength);
    glutReshapeFunc(ChangeSizeLength);

    glutMainLoop();
}
