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
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin); // 상단에서 하단으로 진행
        GLfloat width = topWidth + (bottomWidth - topWidth) * t;

        glLineWidth(width);
        glBegin(GL_LINES);
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
    glutCreateWindow("week09_01");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
}

/* [week09_01 시험 요약]
 * - week08_05 패턴을 독립 타깃으로 분리한 복습용 파일이다.
 * - 선 두께/좌표 보간 문제를 단일 창에서 빠르게 확인하는 목적이다.
 */
