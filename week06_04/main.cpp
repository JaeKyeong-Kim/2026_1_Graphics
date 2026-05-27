#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <stdio.h>

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0f);

    const int pointCount = 180;
    const float radius = 150.0f;
    const float Pi = 3.14f;

    glBegin(GL_POINTS);
    for (int i = 0; i < pointCount; ++i)
    {
        float a = (2 * Pi * i) / pointCount;
        float x = std::cos(a);
        float y = std::sin(a);
        glVertex3f(x * radius, y * radius, 0.0f);
    }
    glEnd();

    glutSwapBuffers();
}

/* [week06_04 시험 요약]
 * - 원 배치 공식: x=cos(a), y=sin(a), a는 라디안이다.
 * - 2*pi를 pointCount로 나눠 등간격 각도를 만들고 radius로 크기를 조절한다.
 */

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 250;
    GLfloat aspectRatio;

    if (h == 0)
        h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h)
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -100.0, 100.0);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -100.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week06_04");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}
