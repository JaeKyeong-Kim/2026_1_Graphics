#if defined(__APPLE__) // macOS에서는 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>
#else
#include <GL/glut.h>   // 그 외 환경에서는 일반 GLUT 헤더를 사용한다.
#endif

#include <cmath>       // sin, cos 계산에 사용한다.

#define GL_PI 3.14159265f // 원형 fan 계산용 PI 값이다.

int gWindow = 0;       // 생성된 GLUT 창 핸들을 저장한다.
bool bCull = true;     // 후면 제거 사용 여부다.
bool bDepth = true;    // depth test 사용 여부다.

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

    DrawCircle(20.0f, 10.0f, 0.0f, 0.0f, 1.0f); // z=10의 큰 파란 원이다.
    DrawCircle(10.0f, 20.0f, 1.0f, 0.0f, 0.0f); // z=20의 작은 빨간 원이다.

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

/* [week17_03 정리]
 * - 동일한 xy 위치에 두 원을 두고 depth test와 cull face 결과를 보는 예제다.
 * - 현재 카메라는 -z 방향을 보므로, z=10과 z=20 원은 eye space에서 카메라 뒤쪽에 놓인다.
 * - 그래서 좌표, lookAt 방향, glOrtho near/far 부호를 함께 해석해야 어떤 원이 보이는지 설명할 수 있다.
 * - 이 파일은 "카메라 방향을 바꿀 때 depth와 컬링 결과가 같이 달라진다"는 점을 확인하기 위한 기준 코드다.
 */
