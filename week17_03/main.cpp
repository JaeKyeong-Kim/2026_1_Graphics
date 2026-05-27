#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>

#define GL_PI 3.14159265f

int gWindow = 0;
bool bCull = true;
bool bDepth = true;

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경은 검은색으로 고정한다.
    glShadeModel(GL_FLAT);                // 각 원은 단일 색으로 채운다.
}

void DrawCircle(float radius, float zPos, float red, float green, float blue)
{
    const int triangleCount = 32;

    glBegin(GL_TRIANGLE_FAN);
        glColor3f(red, green, blue);      // fan 전체에 적용할 색을 지정한다.
        glVertex3f(0.0f, 0.0f, zPos);     // 원의 중심점이다.

        for (int i = 0; i <= triangleCount; ++i)
        {
            float theta = 2.0f * GL_PI * i / triangleCount; // 현재 조각의 각도다.
            float xPos = radius * std::cos(theta);          // 원 둘레의 x좌표다.
            float yPos = radius * std::sin(theta);          // 원 둘레의 y좌표다.
            glVertex3f(xPos, yPos, zPos);                   // 같은 z평면의 둘레 점을 추가한다.
        }
    glEnd();
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.0,  // eye: 카메라 위치
              0.0, 0.0, -1.0, // center: 카메라가 바라보는 방향
              0.0, 1.0, 0.0); // up: 화면 위쪽 기준

    DrawCircle(20.0f, 10.0f, 0.0f, 0.0f, 1.0f);
    DrawCircle(10.0f, 20.0f, 1.0f, 0.0f, 0.0f);

    glutSwapBuffers();
}

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("week17_03");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
    return 0;
}
