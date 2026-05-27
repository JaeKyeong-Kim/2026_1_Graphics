#if defined(__APPLE__) // macOS에서는 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>
#else
#include <GL/glut.h>   // 그 외 환경에서는 일반 GLUT 헤더를 사용한다.
#endif

#include <cmath>       // 삼각함수 계산에 사용한다.

#define GL_PI 3.1415f  // 원형 밑면과 원뿔 계산용 PI 값이다.

int gWindow = 0;       // 생성된 GLUT 창 핸들을 저장한다.

GLfloat xRot = 0.0f;   // x축 회전 각도다.
GLfloat yRot = 0.0f;   // y축 회전 각도다.
GLfloat xTran = 0.0f;  // x축 이동량이다.
GLfloat yTran = 0.0f;  // y축 이동량이다.
bool bCull = true;     // 후면 제거 사용 여부다.
bool bDepth = true;    // depth test 사용 여부다.
bool bOutline = true;  // 뒷면을 선 모드로 바꿀지 여부다.
const GLfloat kMoveStep = 5.0f; // 키 한 번당 이동량이다.

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    if (bOutline)
        glPolygonMode(GL_BACK, GL_LINE);   // 뒷면 삼각형만 선 모드로 바꾼다.
    else
        glPolygonMode(GL_BACK, GL_FILL);   // 뒷면을 다시 채워진 상태로 돌린다.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(xTran, yTran, 0.0f); // 평면 이동을 먼저 적용한다.
        glRotatef(xRot, 1.0f, 0.0f, 0.0f); // x축 회전을 적용한다.
        glRotatef(yRot, 0.0f, 1.0f, 0.0f); // y축 회전을 적용한다.
        DrawConeSide();                    // 현재 변환 상태에서 옆면을 그린다.
        DrawConeBase();                    // 현재 변환 상태에서 밑면을 그린다.
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(400, 400);
    gWindow = glutCreateWindow("week18_test_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);

    glutMainLoop();
    return 0;
}

/* [week18_test_02 정리]
 * - week17_01을 그대로 복사한 두 번째 베이스 파일이다.
 * - week18_test_01과 별개로 다른 조건을 실험할 수 있도록 분리해 둔 상태다.
 * - 기본 렌더링 구조와 입력 구조는 동일하며, 이후 수정 지점만 바꾸면 된다.
 * - outline의 의미는 "전체 골조"가 아니라 GL_BACK 면만 line 모드로 바꾸는 것임을 주의한다.
 */
