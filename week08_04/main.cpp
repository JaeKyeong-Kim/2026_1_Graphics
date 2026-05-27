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
    const GLfloat minWidth = 1.0f;
    const GLfloat maxWidth = 10.0f;
    const GLfloat margin = 12.0f; // 가장자리 클리핑 방지 여백

    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < lineCount; ++i)
    {
        // i(0~9)를 0.0~1.0 구간으로 정규화한다.
        // t=0이면 가장 왼쪽 선, t=1이면 가장 오른쪽 선이 된다.
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);

        // x는 실제 "선의 위치"(세로선의 좌우 위치)다.
        // margin~(worldSize-margin) 사이를 t 비율로 선형 보간해서
        // 10개의 선이 화면 안쪽에 균등 간격으로 배치되게 한다.
        GLfloat x = margin + t * (worldSize - 2.0f * margin);

        // 선 두께도 같은 방식으로 보간한다.
        // t가 커질수록 minWidth -> maxWidth로 증가하므로
        // 왼쪽에서 오른쪽으로 갈수록 선이 두꺼워진다.
        GLfloat width = minWidth + (maxWidth - minWidth) * t;

        glLineWidth(width);
        glBegin(GL_LINES);
        // (x, margin)   : 세로선의 아래 끝점
        // (x, worldSize-margin): 세로선의 위 끝점
        // x를 동일하게 주고 y만 바꿔서 "수직선"을 만든다.
        glVertex2f(x, margin);
        glVertex2f(x, worldSize - margin);
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
    glutCreateWindow("week08_04");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
}

/* [week08_04 시험 요약]
 * - 세로선 10개를 등간격 배치하고 좌->우로 갈수록 선 두께를 증가시킨다.
 * - t 정규화(0~1) 후 x/width를 선형 보간하는 패턴을 기억한다.
 */
