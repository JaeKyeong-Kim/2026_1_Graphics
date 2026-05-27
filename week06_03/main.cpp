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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
        for (int i = 0; i <= 50; ++i)
        {
            glVertex3f(i, i, i);
        }
    glEnd();

    glutSwapBuffers();
}

void ChangeSize(GLsizei w, GLsizei h)
{
    GLint wSize = 250;
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

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week06_03");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week06_03 핵심 정리 - glOrtho에서 z축 범위를 늘려 그릴 수 있는 이유]
===============================================================================

1) 현재 점 데이터
- RenderScene에서 (i, i, i) 형태로 점을 찍으므로 z 값도 0~50까지 증가한다.

2) glOrtho의 마지막 두 인자 의미
- glOrtho(left, right, bottom, top, near, far)
- 여기서 near/far는 "보이는 z 범위(클리핑 구간)"를 뜻한다.

3) 왜 z 범위를 늘려야 하나?
- z 값이 near~far 범위를 벗어나면 해당 정점은 잘려서(clip) 화면에 나오지 않는다.
- 예를 들어 near=-1, far=1 이면 z=50 점은 범위 밖이라 보이지 않는다.

4) 현재 코드에서의 해결
- glOrtho(..., -100.0, 100.0)로 z 허용 범위를 넓혔다.
- 그래서 z=0~50 구간의 점들이 모두 near/far 내부에 들어와 화면에 표시된다.

5) 결론
- x/y 범위만 맞추는 것으로는 부족하고,
  3D 좌표를 쓸 때는 z축 near/far 범위도 데이터 범위를 포함하도록 설정해야 한다.
===============================================================================
*/

/* [week06_03 Notes 보강]
 * - z축 데이터를 쓰면 glOrtho의 near/far 범위를 데이터 범위에 맞춰 잡아야 한다.
 */
