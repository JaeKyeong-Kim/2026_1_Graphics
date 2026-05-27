#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

int gWindowSpacing = 0;
int gWindowLength = 0;

void RenderSceneSpacing(void)
{
    std::cout << "RenderSceneSpacing" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat worldSize = 800.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, worldSize, 0.0, worldSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const int lineCount = 10;
    const GLfloat margin = 12.0f; // 가장자리 클리핑 방지 여백

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE); // GL_LINE_STIPPLE를 활성화해서 이후 GL_LINES가 점선 패턴으로 rasterize 되도록 한다.

    for (int i = 0; i < lineCount; ++i)
    {
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin);
        GLint factor = 4 - static_cast<GLint>(3.0f * t + 0.5f); // 위쪽은 factor가 커서 패턴 간격이 넓고, 아래쪽은 factor가 작아서 간격이 좁다.

        glLineStipple(factor, 0x00FF); // factor만 바꿔 동일한 16비트 마스크를 더 길게 또는 더 촘촘하게 반복한다.
        glBegin(GL_LINES);
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glDisable(GL_LINE_STIPPLE); // 점선 상태를 해제해서 이후 렌더링이 기본 실선 규칙을 그대로 따르도록 복구한다.

    glutSwapBuffers();
}

void RenderSceneLength(void)
{
    std::cout << "RenderSceneLength" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    const GLfloat worldSize = 800.0f;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, worldSize, 0.0, worldSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    const int lineCount = 10;
    const GLfloat margin = 12.0f;

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glEnable(GL_LINE_STIPPLE); // GL_LINE_STIPPLE를 활성화해서 수평선도 같은 스티플 규칙으로 점선 처리한다. 

    for (int i = 0; i < lineCount; ++i)   
    {
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin);

        GLint onBits = 12 - i; // 위쪽은 on 구간을 길게, 아래쪽은 점점 짧게 만들기 위해 12비트에서 3비트까지 줄여간다.
        GLushort pattern = static_cast<GLushort>(((1u << onBits) - 1u) << (16 - onBits)); // onBits만큼 1을 왼쪽부터 채워 16비트 마스크를 직접 만든다.

        glLineStipple(1, pattern); // factor는 고정하고 pattern만 바꿔서 16비트 마스크의 on/off 길이를 직접 다르게 만든다.
        glBegin(GL_LINES);
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glDisable(GL_LINE_STIPPLE); // 스티플 상태를 꺼서 이 렌더 경로 밖의 도형에는 점선 효과가 남지 않게 한다.

    glutSwapBuffers();
}

void ChangeSizeSpacing(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void ChangeSizeLength(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
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
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    gWindowSpacing = glutCreateWindow("week11_01 - stipple spacing");
    SetupRC();
    glutDisplayFunc(RenderSceneSpacing);
    glutReshapeFunc(ChangeSizeSpacing);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(760, 100);
    gWindowLength = glutCreateWindow("week11_01 - stipple length");
    SetupRC();
    glutDisplayFunc(RenderSceneLength);
    glutReshapeFunc(ChangeSizeLength);

    glutMainLoop();
}

/* [week11_01 - copied from week10_01]
 * - Multi-window example: two GLUT windows in one process.
 * - Left window: horizontal lines with different stipple spacing (factor changes).
 * - Right window: horizontal lines with different stipple dash length (pattern changes).
 */
