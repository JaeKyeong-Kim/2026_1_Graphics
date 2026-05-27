#if defined(__APPLE__)                              // macOS 환경이면 Apple GLUT 헤더를 사용한다.
#include <GLUT/glut.h>                              // macOS 기본 GLUT 프레임워크 헤더를 포함한다.
#else                                               // macOS가 아닌 환경 분기다.
#include <GL/glut.h>                                // 일반 GLUT 헤더를 포함한다.
#endif

#include <iostream>                                 // 콘솔 로그 출력에 사용한다.
#include <stdio.h>                                  // 기존 코드 흐름을 유지하기 위한 C 표준 헤더다.

// 장면 렌더링 함수: 직교 투영 좌표계 안에서 사각형을 그린다.
void RenderScene(void)
{
    std::cout << "RenderScene" << std::endl;       // 디스플레이 콜백 호출 여부를 콘솔에 남긴다.
    glClear(GL_COLOR_BUFFER_BIT);                   // 현재 clear color(파란색)로 화면 버퍼를 지운다.

    // 왼쪽 아래는 (0,0)으로 고정한다.
    // viewport의 폭을 250, 높이를 500으로 잡으면
    // glRectf의 정사각형이 화면에서는 가로:세로 = 1:2 직사각형처럼 보인다.
    glViewport(0, 0, 250, 500);

    glColor3f(1.0f, 0.0f, 0.0f);                    // 이후 도형의 현재 색상을 빨간색으로 설정한다.

    // 좌표계는 -1~1 범위이고, 이 사각형은 가로/세로 각각 0.5만큼 차지한다.
    // 즉 viewport 기준으로 가로 1/4, 세로 1/4 크기를 차지한다.
    glRectf(-0.25f, 0.25f, 0.25f, -0.25f);

    glutSwapBuffers();                              // 더블 버퍼링 결과를 실제 화면에 표시한다.
}

// 렌더링 컨텍스트 초기 설정 함수다.
void SetupRC(void)
{
    std::cout << "SetupRC" << std::endl;           // 초기화 함수 호출 여부를 콘솔에 남긴다.
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);          // 배경색을 파란색으로 지정한다.

    glMatrixMode(GL_PROJECTION);                    // 투영 행렬 설정을 시작한다.
    glLoadIdentity();                               // 기존 투영 행렬 상태를 초기화한다.
    glOrtho(-1, 1, -1, 1, -1, 1);                  // 화면 중심이 원점인 직교 좌표계를 설정한다.

    glMatrixMode(GL_MODELVIEW);                     // 이후 도형 그리기를 위해 모델뷰 모드로 되돌린다.
    glLoadIdentity();                               // 모델뷰 행렬도 초기화한다.
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // GLUT 시스템을 초기화한다.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // 더블 버퍼링 + RGB 모드로 창을 생성한다.
    glutInitWindowSize(500, 500);                   // 창 크기를 500x500으로 설정한다.
    glutInitWindowPosition(500, 500);               // 창의 초기 위치를 설정한다.
    glutCreateWindow("week04_03");                  // 창 제목을 week04_03으로 지정한다.

    SetupRC();                                      // 배경색, 투영 좌표계 등 초기 상태를 설정한다.
    glutDisplayFunc(RenderScene);                   // 디스플레이 콜백으로 RenderScene을 등록한다.

    glutMainLoop();                                 // 이벤트 루프를 시작한다.
}

/*
===============================================================================
  [week04_03 요약]
===============================================================================
1. glRectf(-0.25f, 0.25f, 0.25f, -0.25f) 자체는 정사각형이다.
2. glOrtho(-1, 1, -1, 1, -1, 1) 에서 이 도형은 viewport 기준 가로 1/4, 세로 1/4를 차지한다.
3. 하지만 viewport를 (0, 0, 250, 500)으로 잡아 가로/세로 비율을 다르게 만들었다.
4. 그래서 최종 화면에서는 빨간 도형이 가로가 세로의 1/2인 직사각형으로 보인다.
5. 왼쪽 아래 기준점은 (0,0)으로 유지된다.
===============================================================================
*/

/* [week04_03 Notes 보강]
 * - 정사각형 데이터라도 viewport 종횡비가 다르면 직사각형처럼 보일 수 있다.
 */
