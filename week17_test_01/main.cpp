#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

#define GL_PI 3.1415f

int gWindow = 0;

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat xTran = 0.0f;
GLfloat yTran = 0.0f;
bool bCull = true;
const GLfloat kMoveStep = 5.0f;

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_FLAT);
}

void SpecialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
        xRot -= 2.0f;
    else if (key == GLUT_KEY_DOWN)
        xRot += 2.0f;
    else if (key == GLUT_KEY_LEFT)
        yRot -= 2.0f;
    else if (key == GLUT_KEY_RIGHT)
        yRot += 2.0f;

    if (xRot > 360.0f)
        xRot -= 360.0f;
    if (xRot < 0.0f)
        xRot += 360.0f;
    if (yRot > 360.0f)
        yRot -= 360.0f;
    if (yRot < 0.0f)
        yRot += 360.0f;

    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == 'a' || key == 'A')
        xTran -= kMoveStep;
    else if (key == 'd' || key == 'D')
        xTran += kMoveStep;
    else if (key == 'w' || key == 'W')
        yTran += kMoveStep;
    else if (key == 'x' || key == 'X')
        yTran -= kMoveStep;

    glutPostRedisplay();
}

void DrawConeBase(void)
{
    const int sliceCount = 16;
    const float radius = 50.0f;

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= sliceCount; ++i)
        {
            if (i % 2 == 0)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(0.0f, 1.0f, 0.0f);

            float theta = -2.0f * GL_PI * i / sliceCount;
            float xPos = radius * std::cos(theta);
            float yPos = radius * std::sin(theta);
            glVertex3f(xPos, yPos, 0.0f);
        }
    glEnd();
}

void DrawConeSide(void)
{
    const int sliceCount = 16;
    const float radius = 50.0f;
    const float height = 80.0f;

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, height);
        for (int i = 0; i <= sliceCount; ++i)
        {
            if ((i + 1) % 2 == 0)
                glColor3f(0.0f, 1.0f, 0.0f);
            else
                glColor3f(1.0f, 0.0f, 0.0f);

            float theta = 2.0f * GL_PI * i / sliceCount;
            float xPos = radius * std::cos(theta);
            float yPos = radius * std::sin(theta);
            glVertex3f(xPos, yPos, 0.0f);
        }
    glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix(); 
        glTranslatef(xTran, yTran, 0.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);

        DrawConeSide();
        DrawConeBase();
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
    gWindow = glutCreateWindow("week17_test_01");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);

    glutMainLoop();
    return 0;
}
