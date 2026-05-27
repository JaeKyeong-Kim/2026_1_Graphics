#if defined(__APPLE__) // macOS에서는 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>
#else
#include <GL/glut.h>   // 그 외 환경에서는 일반 GLUT 헤더를 사용한다.
#endif

#include <cmath>       // sin, cos 계산에 사용한다.

#define GL_PI 3.1415f  // 원형 밑면 계산용 PI 값이다.

int gWindow = 0;       // 생성된 GLUT 창 핸들을 저장한다.

GLfloat xRot = 0.0f;   // x축 회전 각도다.
GLfloat yRot = 0.0f;   // y축 회전 각도다.
bool bCull = true;     // 후면 제거 사용 여부다.

void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 배경을 검은색으로 설정한다.
    glShadeModel(GL_FLAT);                // 단색 셰이딩을 사용한다.
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

void DrawConeBase(void) // 원뿔의 밑면을 triangle fan으로 그린다.
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

void DrawConeSide(void) // 원뿔의 옆면을 triangle fan으로 그린다.
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
    glClear(GL_COLOR_BUFFER_BIT);         // 화면을 매 프레임 초기화한다.

    if (bCull)                            // 컬링이 켜져 있으면 뒷면 제거를 사용한다.
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    glMatrixMode(GL_MODELVIEW);           // 모델뷰 행렬을 사용할 준비를 한다.
    glLoadIdentity();                     // 이전 프레임 변환을 초기화한다.

    glPushMatrix();
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // 위/아래 화살표 회전을 적용한다.
        glRotatef(yRot, 0.0f, 1.0f, 0.0f); // 좌/우 화살표 회전을 적용한다.

        DrawConeSide();                    // 옆면을 먼저 그린다.
        DrawConeBase();                    // 밑면을 이어서 그린다.
    glPopMatrix();

    glutSwapBuffers();                    // 더블 버퍼 화면을 교체한다.
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
    gWindow = glutCreateWindow("week16_test_01");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeyboard);

    glutMainLoop();
    return 0;
}

/* [week16_test_01 정리]
 * - week16_01 기반의 원뿔 테스트 파일이다.
 * - 화살표 키로 회전시키면서 밑면과 옆면의 앞/뒷면 판정을 확인하는 용도다.
 * - 밑면은 -theta를 사용해 아래에서 볼 때 앞면으로 보이도록 winding을 맞췄다.
 * - glEnable(GL_CULL_FACE)를 켜면 카메라 기준 뒷면은 제거된다.
 */
