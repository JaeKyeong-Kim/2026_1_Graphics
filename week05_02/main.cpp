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
    // 초기 창(500x500) 기준 한 변 1/4(=125)인 정사각형을 화면 정중앙에 배치
    glRectf(-62.5f, 62.5f, 62.5f, -62.5f);

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
        glOrtho(-wSize, wSize, -wSize / aspectRatio, wSize / aspectRatio, -1.0, 1.0);
    else
        glOrtho(-wSize * aspectRatio, wSize * aspectRatio, -wSize, wSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutPostRedisplay();
}

void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("week05_02");

    SetupRC();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);

    glutMainLoop();
}

/*
===============================================================================
[week05_02 개념 정리 - 다음에 다시 봐도 이해되도록 핵심만 정리]
===============================================================================

1) 이 코드의 목표
- 창 크기(w, h)를 사용자가 바꿔도 빨간 도형이 항상 "정사각형"으로 보이게 만든다.
- 정사각형의 기준 좌표는 glRectf(-62.5, 62.5, 62.5, -62.5) 이므로
    월드 좌표에서 한 변 길이는 125로 고정되어 있다.

2) Viewport와 Projection 역할 구분
- glViewport(0, 0, w, h):
    현재 창 전체를 렌더링 결과가 표시될 픽셀 영역으로 지정한다.
    ("어디에 그릴지"를 정함)
- glOrtho(...):
    월드 좌표를 어떤 범위로 볼지(투영 박스)를 정한다.
    ("어떤 스케일로 볼지"를 정함)

3) 왜 창 비율이 바뀌어도 정사각형이 유지되나?
- 핵심은 ChangeSize()에서 aspectRatio = w / h 를 계산하고,
    그 값으로 glOrtho 범위를 보정하는 것.
- 이 보정 덕분에 화면에서 x축 1단위와 y축 1단위 픽셀 길이가 같아진다.
- 따라서 월드 좌표에서 가로=세로인 도형은 화면에서도 가로=세로가 된다.

4) w <= h 와 w > h 분기 의미
- w <= h (세로가 더 길거나 정사각형 창):
    x 범위는 [-wSize, wSize]로 고정(폭 500 기준),
    y 범위를 aspectRatio로 확장해서 세로가 늘어난 창 비율을 보정한다.
- w > h (가로가 더 긴 창):
    y 범위는 [-wSize, wSize]로 고정(높이 500 기준),
    x 범위를 aspectRatio로 확장해서 가로가 늘어난 창 비율을 보정한다.

5) wSize = 250의 의미
- "항상 정확히 500x500으로 고정"이라는 뜻은 아니다.
- 작은 축 쪽을 500 기준(= 2*wSize)으로 잡고,
    큰 축 쪽은 aspectRatio에 맞춰 확장한다는 뜻이다.

6) 정리 한 줄
- 정사각형 유지의 본질은
    "정사각형으로 정의된 도형(glRectf) + 비율 보정된 투영(glOrtho)"의 결합이다.
===============================================================================
*/

/* [week05_02 Notes 보강]
 * - D5/6 문서 보충: glScissor를 쓰면 viewport 전체가 아닌 특정 사각형만
 *   clear/그리기 대상으로 제한할 수 있다.
 */
