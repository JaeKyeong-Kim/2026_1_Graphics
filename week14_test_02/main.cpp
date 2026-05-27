#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

int gWindow = 0;

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderScene(void)
{
    const int triangleCount = 16;
    const float radius = 50.0f;
    const float pi = 3.14159265358979323846f;

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= triangleCount; ++i)
        {
            float theta = 2.0f * pi * i / triangleCount;
            float x = radius * std::cos(theta);
            float y = radius * std::sin(theta);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    glPointSize(8.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < triangleCount; ++i)
        {
            float theta = 2.0f * pi * i / triangleCount;
            float x = radius * std::cos(theta);
            float y = radius * std::sin(theta);
            glVertex3f(x, y, 0.0f);
        }
    glEnd();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 100;
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("week14_test_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
