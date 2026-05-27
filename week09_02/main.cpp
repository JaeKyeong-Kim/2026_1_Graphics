#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

int gWindowVertical = 0;
int gWindowHorizontal = 0;

void RenderSceneVertical(void)
{
    std::cout << "RenderSceneVertical" << std::endl;
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
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat x = margin + t * (worldSize - 2.0f * margin);
        GLfloat width = minWidth + (maxWidth - minWidth) * t;

        glLineWidth(width);
        glBegin(GL_LINES);
        glVertex2f(x, margin);
        glVertex2f(x, worldSize - margin);
        glEnd();
    }

    glutSwapBuffers();
}

void RenderSceneHorizontal(void)
{
    std::cout << "RenderSceneHorizontal" << std::endl;
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
    const GLfloat margin = 12.0f;

    glColor3f(1.0f, 1.0f, 1.0f);

    for (int i = 0; i < lineCount; ++i)
    {
        GLfloat t = static_cast<GLfloat>(i) / static_cast<GLfloat>(lineCount - 1);
        GLfloat y = (worldSize - margin) - t * (worldSize - 2.0f * margin);
        GLfloat width = topWidth + (bottomWidth - topWidth) * t;

        glLineWidth(width);
        glBegin(GL_LINES);
        glVertex2f(margin, y);
        glVertex2f(worldSize - margin, y);
        glEnd();
    }

    glutSwapBuffers();
}

void ChangeSizeVertical(GLsizei w, GLsizei h)
{
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void ChangeSizeHorizontal(GLsizei w, GLsizei h)
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
    gWindowVertical = glutCreateWindow("week09_02 - week08_04 (Vertical)");
    SetupRC();
    glutDisplayFunc(RenderSceneVertical);
    glutReshapeFunc(ChangeSizeVertical);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(760, 100);
    gWindowHorizontal = glutCreateWindow("week09_02 - week08_05 (Horizontal)");
    SetupRC();
    glutDisplayFunc(RenderSceneHorizontal);
    glutReshapeFunc(ChangeSizeHorizontal);

    glutMainLoop();
}

/* [week09_02 시험 요약]
 * - GLUT 멀티 윈도우 예제: 창 2개를 한 실행 파일에서 동시에 띄운다.
 * - 창별 glutDisplayFunc/glutReshapeFunc를 따로 등록해 독립 렌더링한다.
 * - 창A는 week08_04(세로선), 창B는 week08_05(가로선) 로직을 재사용한다.
 */
