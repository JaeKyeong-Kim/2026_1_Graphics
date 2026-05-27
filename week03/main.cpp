#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdio.h>

//장면 렌더링
void RenderScene(void)
{
    std::cout << "RenderScene" <<std::endl;
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, 500, 500); // 포트 설정, 이거 정확히 역할 알아보기

    glColor3f(1.0f, 0.0f, 0.0f); // 아래의 도형을 빨간색으로 그리기
    // glRectf(-0.5f, -0.5f, 0.5f, 0.5f); // 사각형 그리기. 이 경우에는 정사각형 (왼쪽 아래 (-0.5, -0.5), 오른쪽 위 (0.5, 0.5))
    glRectf(-0.25f, -0.25f, 0.25f, 0.25f); // 사각형 한 변의 길이가 창 길이의 1/4이 되게 표현

    glutSwapBuffers();
}

/* [week03 시험 요약]
 * - week02 렌더링 구조를 반복 학습하는 확장 주차다.
 * - 투영 범위(glOrtho)와 viewport 해석이 도형 위치/비율을 결정한다.
 * - 창 비율 문제는 projection/viewport 관점으로 설명할 수 있어야 한다.
 */

void SetupRC(void)
{
    std::cout << "SetupRC" <<std::endl;
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 배경용 RGB값 설정
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // 이 부분 때문에 원래 정사각형이 나와야 하는데 직사각형으로 화면에 나옴. 여기를 가로세로 같게 만들면 정상적으로 정사각형이 나옴
    glutInitWindowPosition(100, 100);
    glutCreateWindow("week03");

    SetupRC();
    glutDisplayFunc(RenderScene);

    glutMainLoop();
    
}
