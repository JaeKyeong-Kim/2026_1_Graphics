#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat worldSize = 800.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, worldSize, 0.0, worldSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const int lineCount = 10;
    const GLfloat topWidth = 10.0f;
    const GLfloat bottomWidth = 1.0f;
    const GLfloat margin = 12.0f; // 가장자리 클리핑 방지 여백

    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < lineCount; ++i)
    {
        // i(0~9)를 0.0~1.0 구간으로 정규화한다.
        // t=0은 가장 위 선, t=1은 가장 아래 선에 대응된다.
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);

        // y는 실제 "선의 위치"(가로선의 상하 위치)다.
        // 위쪽(worldSize-margin)에서 시작해 아래쪽(margin)으로 내려오도록
        // t 비율만큼 선형 보간해 10개 선을 균등 간격으로 배치한다.
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin); // 상단에서 하단으로 진행

        // 두께는 topWidth -> bottomWidth로 보간한다.
        // 즉 위에서 아래로 갈수록 점점 얇아진다.
        GLfloat width = topWidth + (bottomWidth - topWidth) * t;

        glLineWidth(width);
        glBegin(GL_LINES);
        // (margin, y)            : 가로선의 왼쪽 끝점
        // (worldSize-margin, y)  : 가로선의 오른쪽 끝점
        // y를 동일하게 주고 x만 바꿔서 "수평선"을 만든다.
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glutSwapBuffers();
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
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week08_05");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
}

/* [week08_05 시험 요약]
 * - 가로선 10개를 등간격 배치하고 상->하로 갈수록 선 두께를 감소시킨다.
 * - t 정규화 후 y/width 보간, margin으로 클리핑 방지하는 구성이 핵심이다.
 */
