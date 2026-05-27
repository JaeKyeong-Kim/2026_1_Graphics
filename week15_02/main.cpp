#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

int gWindow = 0;
GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat xTran = 0.0f;
GLfloat yTran = 0.0f;
bool bCull = false;

void SetupRC(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a')
        xTran -= 2.0f;
    else if (key == 'd')
        xTran += 2.0f;
    else if (key == 'w')
        yTran += 2.0f;
    else if (key == 'x')
        yTran -= 2.0f;

    glutPostRedisplay();
}

void RenderScene(void)
{
    const int triangleCount = 32;
    const float radius = 50.0f;
    const float pi = 3.14159265f;

    glClear(GL_COLOR_BUFFER_BIT);

    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glTranslatef(xTran, yTran, 0.0f); // x와 y 이동을 한 번에 적용한다. 수업 설명처럼 축별로 따로 써도 동작은 같다.

        glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            for (int i = 0; i <= triangleCount; ++i)
            {
                if (i == 1)
                    glColor3f(0.0f, 0.0f, 1.0f);
                else if (i % 2 == 0)
                    glColor3f(1.0f, 0.0f, 0.0f);
                else
                    glColor3f(0.0f, 1.0f, 0.0f);

                float theta = 2.0f * pi * i / triangleCount;
                float xPos = radius * std::cos(theta);
                float yPos = radius * std::sin(theta);
                glVertex3f(xPos, yPos, 0.0f);
            }
        glEnd();
    glPopMatrix();

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
    gWindow = glutCreateWindow("week15_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();
    return 0;
}
